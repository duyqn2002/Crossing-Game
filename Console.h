#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>

#include "Constants.h"
#include "CPOINT2D.h"
#include "Texture.h"

// Apply double buffering to render console game
class Console {
private:
	unsigned int mHeight;
	unsigned int mWidth;

	HANDLE m_hScreenBufferOne;
	HANDLE m_hScreenBufferTwo;
	HANDLE* m_hActiveScreenBuffer;
	HANDLE* m_hBackgroundScreenBuffer;
public:
	Console();
	Console(unsigned int, unsigned int);
	Console(unsigned int, unsigned int, unsigned int, unsigned int);
	Console(const Console&);
	~Console();

	unsigned int Height() const;
	unsigned int Width() const;

	void FixedConsoleWindow() const;
	void DrawPixels(int, int, char, COLOUR = COLOUR::WHITE, int = 1) const;
	void DrawBorder(CPOINT2D, CPOINT2D, COLOUR = COLOUR::WHITE) const;
	void DrawObject(int, int, const Texture&, COLOUR = COLOUR::WHITE) const;
	void ClearScreen() const;
	void Render();
};

#endif // CONSOLE_H
