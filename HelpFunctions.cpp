#include "HelpFunctions.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void ShowCursorConsole(bool isVisible) {
	// Source: https://stackoverflow.com/a/30126700
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = isVisible;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void ConstructConsole(int width, int height, int fontw, int fonth)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT rectWindow = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &rectWindow);

	// Set the screen buffer size
	COORD coord = { (short)width, (short)height };
	if (!SetConsoleScreenBufferSize(hConsole, coord))
		return;

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(hConsole))
		return;

	// Set the font width and font height of console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;

	if (!SetCurrentConsoleFontEx(hConsole, false, &cfi))
		return;

	// Check if valid width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	if (height > csbi.dwMaximumWindowSize.Y)
		return;
	if (width > csbi.dwMaximumWindowSize.X)
		return;

	// Set the console width and height
	rectWindow = { 0, 0, (short)width - 1, (short)height - 1 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &rectWindow))
		return;

	// No resize window
	FixConsoleWindow();

	// Hide the cursor
	ShowCursorConsole(false);
}

void CenterConsole(int width, int height) {
	// 
	HWND hConsoleWnd = GetConsoleWindow();
	HMONITOR hMonitor = MonitorFromWindow(hConsoleWnd, MONITOR_DEFAULTTONEAREST);

	// Align the console to center of screen
	if (hMonitor)
	{
		MONITORINFO info{ sizeof(info) }; // set cbSize member and fill the rest with zero
		if (GetMonitorInfo(hMonitor, &info))
		{
			int x = (info.rcWork.left + info.rcWork.right) / 2 - width / 2;
			int y = (info.rcWork.top + info.rcWork.bottom) / 2 - height / 2;

			SetWindowPos(hConsoleWnd, nullptr, x, y, width, height,
				SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE);
		}
	}

	//MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = (short)x;
	coord.Y = (short)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int GetHeightConsoleWindowBuffer() {
	int height = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		height = csbi.srWindow.Bottom - csbi.srWindow.Left;
	}

	return height;
}

int GetWidthConsoleWindowBuffer() {
	int width = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		width = csbi.srWindow.Right - csbi.srWindow.Left;
	}

	return width;
}

int GetWidthAsciiArt(string art) {
	int lengthStr = (int)art.length();
	int width = 0;
	int count = 0;

	for (int index = 0; index < lengthStr; index++) {
		if (art[index] == '\n') {
			width = max(count, width);
			count = 0;
			continue;
		}
		count++;

	}

	return width;
}

int GetHeightAsciiArt(string art) {
	stringstream sstream(art);
	string temp;
	int height = 0;

	while (!sstream.eof()) {
		getline(sstream, temp, '\n');
		height++;
	}

	return height;
}

int RandomInt(int MAX, int MIN) {
	random_device randDevice;
	int range = MAX - MIN + 1;
	return randDevice() % range + MIN;
}

void TextColor(COLOUR color) {
	HANDLE hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, (int)color);
}