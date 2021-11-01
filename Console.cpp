#include "Console.h"

Console::Console() {
	m_bSwitcher = false;
	m_hScreenBufferOne = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hScreenBufferTwo = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hActiveScreenBuffer = &m_hScreenBufferOne;
	m_hBackgroundScreenBuffer = &m_hScreenBufferTwo;
}

Console::Console(unsigned int width, unsigned int height) : Console(){
	SMALL_RECT rectWindow = { 0 ,0, width, height };

	SetConsoleWindowInfo(m_hScreenBufferOne, TRUE, &rectWindow);
	SetConsoleWindowInfo(m_hScreenBufferTwo, TRUE, &rectWindow);
}

Console::Console(unsigned int width, unsigned int height,unsigned int fontw, unsigned int fonth) : Console(width,height) {
	SMALL_RECT rectWindow;

	//// Set the screen buffer size
	COORD coord = { (short)width, (short)height };
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

	// Check if valid width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(m_hScreenBufferOne, &csbi))
		return;
	if (height > csbi.dwMaximumWindowSize.Y)
		return;
	if (width > csbi.dwMaximumWindowSize.X)
		return;

	// Set the console width and height
	rectWindow = { 0, 0, (short)width - 1, (short)height - 1 };
	if (!SetConsoleWindowInfo(m_hScreenBufferOne, TRUE, &rectWindow))
		return;
	if (!SetConsoleWindowInfo(m_hScreenBufferTwo, TRUE, &rectWindow))
		return;

	FixedConsoleWindow();
	ShowCursorConsole(false);
}

Console::~Console() {}

void Console::FixedConsoleWindow() const{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Console::ShowCursorConsole(bool isVisible) const{
	// Source: https://stackoverflow.com/a/30126700
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = isVisible;
	SetConsoleCursorInfo(*m_hBackgroundScreenBuffer, &info);
}

void Console::GotoXY(int x,int y) const{
	COORD coord;
	coord.X = (short)x;
	coord.Y = (short)y;
	SetConsoleCursorPosition(*m_hBackgroundScreenBuffer, coord);
}

unsigned int Console::Height() const {
	unsigned int height = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(*m_hActiveScreenBuffer, &csbi))
	{
		height = csbi.srWindow.Bottom - csbi.srWindow.Left;
	}

	return height;
}

unsigned int Console::Width() const {
	unsigned int width = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(*m_hActiveScreenBuffer, &csbi))
	{
		width = csbi.srWindow.Right - csbi.srWindow.Left;
	}

	return width;
}

void Console::Draw(int x, int y, char c, COLOUR color,int nChar) const{
	DWORD written;
	FillConsoleOutputCharacterA(*m_hBackgroundScreenBuffer, c, nChar, { (short)x,(short)y}, &written);
	FillConsoleOutputAttribute(*m_hBackgroundScreenBuffer, (int)color, nChar, { (short)x,(short)y }, &written);
}

void Console::DrawBorder(CPOINT2D topLeft, CPOINT2D bottomRight, COLOUR color) {
	int x1 = topLeft.getX();
	int y1 = topLeft.getY();

	int x2 = bottomRight.getX();
	int y2 = bottomRight.getY();

	int width = x2 - x1;

	// Draw 2 top corner
	Draw(x1, y1, TOP_LEFT_CORNER, color);
	Draw(x2, y1, TOP_RIGHT_CORNER, color);

	// Draw 2 horizontal line
	Draw(x1 + 1, y1, HORIZONTAL_OUTLINE, color,width - 1);
	Draw(x1 + 1, y2, HORIZONTAL_OUTLINE, color,width - 1);

	// Draw 2 vertical line
	for(int index = y1 + 1; index < y2; index++){
		Draw(x1, index, VERTICAL_OUTLINE, color);
		Draw(x2, index, VERTICAL_OUTLINE, color);
	}

	// Draw 2 bottom corner
	Draw(x1, y2, BOTTOM_LEFT_CORNER, color);
	Draw(x2, y2, BOTTOM_RIGHT_CORNER, color);
}

void Console::DrawObject(int x, int y,const Texture& form, COLOUR color) const {
	vector<string> body = form.GetTexture();
	int currX = x;
	int currY = y;

	for (const auto& line : body) {
		for (const auto& c : line) {
			Draw(currX, currY, c,color);
			currX++;
		}
		currX = x;
		currY++;
	}
}

void Console::ClearScreen() const {
	COORD topLeft = { 0 , 0 };
	CONSOLE_SCREEN_BUFFER_INFO bufferWindowInfo;
	DWORD written;

	GetConsoleScreenBufferInfo(*m_hBackgroundScreenBuffer, &bufferWindowInfo);
	FillConsoleOutputCharacterA(*m_hBackgroundScreenBuffer, ' ', bufferWindowInfo.dwSize.X * bufferWindowInfo.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(*m_hBackgroundScreenBuffer, topLeft);
}

void Console::Render() {
	CONSOLE_SCREEN_BUFFER_INFO windowInfo;
	GetConsoleScreenBufferInfo(&m_hActiveScreenBuffer, &windowInfo);
	SetConsoleScreenBufferSize(&m_hBackgroundScreenBuffer, windowInfo.dwSize);

	// Switch between 2 buffer
	m_bSwitcher = !m_bSwitcher;
	m_hActiveScreenBuffer = (m_bSwitcher == false) ? &m_hScreenBufferOne : &m_hScreenBufferTwo;
	m_hBackgroundScreenBuffer = (m_bSwitcher == false) ? &m_hScreenBufferTwo : &m_hScreenBufferOne;

	SetConsoleActiveScreenBuffer(*m_hActiveScreenBuffer);
}