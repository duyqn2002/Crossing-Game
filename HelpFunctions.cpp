#include "HelpFunctions.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

RECT GetScreenRect(){
	// Get desktop size
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	return desktop;
}

void ResizeConsoleAndCenterConsole(int height, int width) {
	// Get console size
	RECT r = GetScreenRect();
	HWND console = GetConsoleWindow();

	// Align the console to center of screen
	r.left = (r.right - width) / 2;
	r.top = (r.bottom - height) / 2;

	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowCursorConsole(bool isVisible) {
	// Source: https://stackoverflow.com/a/30126700
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = isVisible;
	SetConsoleCursorInfo(consoleHandle, &info);
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

void TextColor(COLOR color) {
	HANDLE hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, (int)color);
}

void DeleteScreen() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}