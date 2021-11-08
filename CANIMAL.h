#ifndef CANIMAL_H
#define CANIMAL_H

#include "CPOINT2D.h"
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

	// Limit left and right X
	int mLeft;
	int mRight;

	double mSpeed;

	// Animal form
	Texture mAnimalLeftForm;
	Texture mAnimalRightForm;
	Texture* mCurrAnimalForm;

	COLOUR mAnimalColour = DEFAULT_COLOUR;

public:
	CANIMAL() = default;
	virtual ~CANIMAL() = default;

	static CANIMAL* createObject(const string&);

	virtual string className() = 0;
	virtual CANIMAL* Clone() = 0;

	// Setter
	void setX(int);
	void setY(int);
	void setXY(int, int);
	void setLimit(int, int);
	void setSpeed(double);
	void setColour(COLOUR);

	// Getter
	int getX() const;
	int getY() const;
	int Width() const;
	int Height() const;
	int getLeft() const;
	int getRight() const;
	int getSpeed() const;

	// Check impact with another animal
	bool isImpact(const CANIMAL&) const;

	// Update method
	virtual void toggleForm();
	virtual void Move(int, int);
	virtual void resetPos();
	virtual void updatePos();

	// Sound
	virtual void Tell() {};

	// Render method
	virtual void drawAnimal(const Console&) const;

protected:
	static CANIMAL* addSample(CANIMAL*);
};

#endif // CANIMAL_H
