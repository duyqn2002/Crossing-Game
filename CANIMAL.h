#ifndef CANIMAL_H
#define CANIMAL_H

#include "Console.h"

class CANIMAL {
private:
	static vector<CANIMAL*> m_vecSampleObjects;

protected:
	// Current position
	CPOINT2D mCurrPos;

	// Width and height of vehicle
	int mHeight;
	int mWidth;

	// Animal form
	Texture mAnimalLeftForm;
	Texture mAnimalRightForm;
	Texture* mCurrAnimalForm;

	COLOUR mAnimalColour = DEFAULT_COLOUR;

public:
	CANIMAL() = default;
	virtual ~CANIMAL() = default;

	static CANIMAL* createObject(const ENEMY&);

	virtual ENEMY className() = 0;
	virtual CANIMAL* Clone() = 0;

	// Setter
	void setX(int);
	void setY(int);
	void setXY(int, int);
	void setColour(COLOUR);

	// Getter
	int getX() const;
	int getY() const;
	int Width() const;
	int Height() const;

	// Update method
	void toggleForm(int);
	void Move(int, int);

	// Sound
	virtual void Tell() {};

	// Render method
	virtual void drawToConsole(int,int,Console&);

protected:
	static CANIMAL* addSample(CANIMAL*);
};

#endif // CANIMAL_H
