#ifndef CONSOLE
#define CONSOLE

#include <Windows.h>
#include "CPOINT2D.h"
#include "Constants.h"
#include "Texture.h"

class Console {
private:
	bool m_bSwitcher;
	HANDLE m_hScreenBufferOne;
	HANDLE m_hScreenBufferTwo;
	HANDLE* m_hActiveScreenBuffer;
	HANDLE* m_hBackgroundScreenBuffer;
public:
	Console();
	Console(unsigned int, unsigned int);
	Console(unsigned int, unsigned int, unsigned int, unsigned int);
	~Console();

	void FixedConsoleWindow() const;
	void ShowCursorConsole(bool) const;
	void GotoXY(int, int) const;

	unsigned int Height() const;
	unsigned int Width() const;

	void Draw(int, int, char, COLOUR = COLOUR::WHITE, int = 1) const;
	void DrawBorder(CPOINT2D, CPOINT2D, COLOUR = COLOUR::WHITE);
	void DrawObject(int, int, const Texture&, COLOUR = COLOUR::WHITE) const;
	void ClearScreen() const;
	void Render();
};
#endif // !CONSOLE
