#ifndef CONSOLE_H
#define CONSOLE_H

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

	Console();
	Console(unsigned int, unsigned int, unsigned int, unsigned int);
	Console(const Console&);
public:
	static Console* getConsole(unsigned int, unsigned int, unsigned int, unsigned int);
	
	~Console();

	unsigned int Height() const;
	unsigned int Width() const;
	string getFilePathToLoad() const;
	string getFilePathToSave() const;

	void SetCursor(bool);
	void FixedConsoleWindow();
	void DrawPixels(int, int, char, COLOUR = COLOUR::WHITE, int = 1);
	void DrawBorder(CPOINT2D, CPOINT2D, COLOUR = COLOUR::WHITE);
	void DrawObject(int, int, const Texture&, COLOUR = COLOUR::WHITE);
	void ClearScreen();
	void Render();
};

#endif // CONSOLE_H
