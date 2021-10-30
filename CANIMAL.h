#ifndef CANIMAL_H
#define CANIMAL_H
#include "HelpFunctions.h"
#include"CPOINT2D.h"


class CANIMAL {
protected:
	CPOINT2D mCurrPos;
	int mStartPosX = 0;

	int mLeft = 0;
	int mRight = 0;

	int mHeight = 0;
	int mWidth = 0;

	DIRECTION mMovingDirection;
	string mAnimalLeftForm;
	string mAnimalRightForm;
	COLOUR mAnimalColour = DEFAULT_COLOUR;

public:
	CANIMAL() = default;
	virtual ~CANIMAL() = default;
	void reset();

	void setXY(int, int);
	void setStartPosX(int);
	void setLeft(int);
	void setRight(int);

	int getX() const;
	int getY() const;

	int Width() const;
	int Height() const;

	virtual void Move(int, int);
	virtual void eraseAnimalHead() const;
	virtual void eraseAnimalTail() const;
	virtual void eraseOldAnimal() const;
	virtual void drawAnimal() const;

	virtual bool isOutSide() const;
	virtual void updatePos(int);

};

#endif // CANIMAL_H
