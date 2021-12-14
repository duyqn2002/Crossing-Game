#ifndef CSCORE_BOARD_H
#define CSCORE_BOARD_H

#include "Console.h"

class CGAME;

class CScoreBoard
{
private:
	// 2 point of a rect
	CPOINT2D mTopLeft;
	CPOINT2D mBottomRight;

	Texture mTitle = \
		" ___\n"
		"/ __| __ ___ _ _ ___\n"
		"\\__ \\/ _/ _ \\ '_/ -_)\n"
		"|___/\\__\\___/_| \\___|\n";
                      
	unsigned int mWidth;
	unsigned int mHeight;

	unsigned int mPaddingTop;

	CScoreBoard();
	CScoreBoard(CPOINT2D, CPOINT2D);
public:
	~CScoreBoard();

	static CScoreBoard* getScoreBoard();

	// Setter
	void setPosTopLeftCorner(CPOINT2D);
	void setPosBottomRightCorner(CPOINT2D);

	// Method
	void resize(int , int);
	void drawScoreBoard(CGAME*);
};

#endif // !CSCORE_BOARD_H


