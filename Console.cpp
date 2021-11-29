#include "Console.h"

Console::Console() {
	m_hScreenBufferOne = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hScreenBufferTwo = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hActiveScreenBuffer = &m_hScreenBufferOne;
	m_hBackgroundScreenBuffer = &m_hScreenBufferTwo;

	mHeight = 1;
	mWidth = 1;

	SetCursor(false);
}

Console::Console(unsigned int width, unsigned int height, unsigned int fontw, unsigned int fonth) : Console() {
	// Construct a console window with height and width, font width and font height
	mHeight = height;
	mWidth = width;

	// Set the console width and height
	SMALL_RECT rectWindow = { 0, 0, (short)mWidth - 1, (short)mHeight - 1 };
	if (!SetConsoleWindowInfo(m_hScreenBufferOne, TRUE, &rectWindow))
		return;
	if (!SetConsoleWindowInfo(m_hScreenBufferTwo, TRUE, &rectWindow))
		return;

	SetConsoleActiveScreenBuffer(*m_hActiveScreenBuffer);

	// Set the screen buffer size
	COORD coord = { (short)mWidth, (short)mHeight};
	if (!SetConsoleScreenBufferSize(m_hScreenBufferOne, coord))
		return;
	if (!SetConsoleScreenBufferSize(m_hScreenBufferTwo, coord))
		return;

	// Set the font width and font height of console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	if (!SetCurrentConsoleFontEx(m_hScreenBufferOne, false, &cfi))
		return;
	if (!SetCurrentConsoleFontEx(m_hScreenBufferTwo, false, &cfi))
		return;

	FixedConsoleWindow();
}

Console* Console::getConsole(unsigned int width, unsigned int height, unsigned int fontw, unsigned int fonth)
{
	static Console mInstance(width, height,fontw,fonth);
	return &mInstance;
}

Console::Console(const Console& other) {
	mHeight = other.mHeight;
	mWidth = other.mWidth;

	m_hScreenBufferOne = other.m_hScreenBufferOne;
	m_hScreenBufferTwo = other.m_hScreenBufferTwo;

	if (other.m_hActiveScreenBuffer == &other.m_hScreenBufferOne) {
		m_hActiveScreenBuffer = &m_hScreenBufferOne;
		m_hBackgroundScreenBuffer = &m_hScreenBufferTwo;
	}
	else {
		m_hActiveScreenBuffer = &m_hScreenBufferTwo;
		m_hBackgroundScreenBuffer = &m_hScreenBufferOne;
	}
}

Console::~Console() {}

unsigned int Console::Height() const {
	return mHeight;
}

unsigned int Console::Width() const {
	return mWidth;
}

void Console::SetCursor(bool visible)
{
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(*m_hActiveScreenBuffer, &lpCursor);
	SetConsoleCursorInfo(*m_hBackgroundScreenBuffer, &lpCursor);
}

void Console::FixedConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Console::DrawPixels(int x, int y, char c, COLOUR color, int nChar) {
	// Draw one or nChar pixel
	DWORD written;
	COORD coord;

	coord.X = (short)x;
	coord.Y = (short)y;

	FillConsoleOutputCharacterA(*m_hBackgroundScreenBuffer, c, nChar, coord, &written);
	FillConsoleOutputAttribute(*m_hBackgroundScreenBuffer, (int)color, nChar, coord, &written);
}

void Console::DrawBorder(CPOINT2D topLeft, CPOINT2D bottomRight, COLOUR color) {
	// Draw a border to buffer
	int x1 = topLeft.getX();
	int y1 = topLeft.getY();

	int x2 = bottomRight.getX();
	int y2 = bottomRight.getY();

	int width = x2 - x1 + 1;

	// Draw 2 horizontal line
	DrawPixels(x1, y1, ' ', color, width);
	DrawPixels(x1, y2, ' ', color, width);

	// Draw 2 vertical line
	for (int index = y1 + 1; index < y2; index++) {
		DrawPixels(x1, index, ' ', color);
		DrawPixels(x2, index, ' ', color);
	}
}

void Console::DrawObject(int x, int y, const Texture& form, COLOUR color) {
	// Draw a object to buffer
	vector<string> body = form.getTexture();
	int currX = x;
	int currY = y;

	for (const auto& line : body) {
		for (const auto& c : line) {
			DrawPixels(currX, currY, c, color);
			currX++;
		}
		currX = x;
		currY++;
	}
}

void Console::ClearScreen() {
	COORD topLeft = { 0 , 0 };
	CONSOLE_SCREEN_BUFFER_INFO bufferWindowInfo;
	DWORD written;

	GetConsoleScreenBufferInfo(*m_hBackgroundScreenBuffer, &bufferWindowInfo);
	FillConsoleOutputCharacterA(*m_hBackgroundScreenBuffer, ' ', bufferWindowInfo.dwSize.X * bufferWindowInfo.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(*m_hBackgroundScreenBuffer, 0, bufferWindowInfo.dwSize.X * bufferWindowInfo.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(*m_hBackgroundScreenBuffer, topLeft);
}

void Console::Render() {
	// Switch between 2 buffer
	if (m_hActiveScreenBuffer == &m_hScreenBufferOne) {
		m_hActiveScreenBuffer = &m_hScreenBufferTwo;
		m_hBackgroundScreenBuffer = &m_hScreenBufferOne;
	}
	else {
		m_hActiveScreenBuffer = &m_hScreenBufferOne;
		m_hBackgroundScreenBuffer = &m_hScreenBufferTwo;
	}

	SetConsoleActiveScreenBuffer(*m_hActiveScreenBuffer);
}