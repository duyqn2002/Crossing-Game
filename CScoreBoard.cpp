#include "CScoreBoard.h"

CScoreBoard::CScoreBoard()
{
	mPaddingTop = 5;
}

CScoreBoard::CScoreBoard(CPOINT2D topLeft, CPOINT2D topRight)
{
	mTopLeft = topLeft;
	mBottomRight = topRight;
}

CScoreBoard* CScoreBoard::getScoreBoard()
{
	static CScoreBoard mScoreBoard;
	return &mScoreBoard;
}

CScoreBoard::~CScoreBoard()
{
}

void CScoreBoard::setPosTopLeftCorner(CPOINT2D topLeft)
{
	mTopLeft = topLeft;
}

void CScoreBoard::setPosBottomRightCorner(CPOINT2D bottomRight)
{
	mBottomRight = bottomRight;
}

void CScoreBoard::resize(int width, int height)
{
	if (width <= 0 || height <= 0)
		return;

	mWidth = width;
	mHeight = height;

	mBottomRight.setXY(mTopLeft.getX() + width - 1, mTopLeft.getY() + height - 1);
}

void CScoreBoard::drawScoreBoard(Console& console)
{
	int centerX = mTopLeft.getX() + mWidth / 2;

	int titleX = centerX - (mTitle.Width() / 2);
	int titleY = mTopLeft.getY() + mPaddingTop;

	string score = "Score: " + to_string(mScore);
	Texture textDisplay;
	textDisplay = score;

	console.DrawBorder(mTopLeft, mBottomRight, COLOUR::CYAN_BG);
	console.DrawObject(titleX, titleY, mTitle);
}
