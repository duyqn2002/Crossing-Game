#include "CGAME.h"
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

void CScoreBoard::drawScoreBoard(CGAME* game)
{
	// Init part
	Console* console = game->getConsole();
	int centerX = mTopLeft.getX() + mWidth / 2;

	int titleX = centerX - (mTitle.Width() / 2);
	int titleY = mTopLeft.getY() + mPaddingTop;

	int x;
	int y = titleY + mTitle.Height() + 1;

	vector<Texture> vecTexts;
	vecTexts.push_back("High Score: " + to_string(game->getHighScore()));
	vecTexts.push_back("Score: " + to_string(game->getScore()));
	vecTexts.push_back("Level: " + to_string(game->getLevel()));

	Texture help = "Help\n" + game->getHelp();

	// Render part
	console->DrawBorder(mTopLeft, mBottomRight, COLOUR::CYAN_BG);
	console->DrawObject(titleX, titleY, mTitle);

	for (const auto& text : vecTexts) {
		x = centerX - (text.Width() / 2);

		console->DrawObject(x, y++, text);
	}

	x = centerX - (help.Width() / 2);
	console->DrawObject(x, y + mPaddingTop, help);
}
