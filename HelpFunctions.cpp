#include "HelpFunctions.h"

void CenterConsole(int width, int height) {
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
}

void GotoXY(int x, int y)  {
	COORD coord;
	coord.X = (short)x;
	coord.Y = (short)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void SetConsoleGameTitle(string title) {
	if (title.size() != 0)
		title = "title " + title;
	else
		title = "title Console";

	system(title.c_str());
}

int GetWidthAsciiArt(const string& art) {
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

int GetHeightAsciiArt(const string& art) {
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