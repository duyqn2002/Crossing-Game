#ifndef CVEHICLE_H
#define CVEHICLE_H

#include "Console.h"

class CVEHICLE {
private:
	static vector<CVEHICLE*> m_vecSampleObjects;

protected:
	// Current position
	CPOINT2D mCurrPos;

	// Width and height of vehicle
	int mHeight = 0;
	int mWidth = 0;

	// Vehicle form
	Texture mVehicleLeftForm;
	Texture mVehicleRightForm;
	Texture* mCurrVehicleForm;

	// Color for vehicle
	COLOUR mVehicleColour = DEFAULT_COLOUR;

public:
	CVEHICLE() = default;
	virtual ~CVEHICLE() = default;

	static CVEHICLE* createObject(const ENEMY&);

	virtual ENEMY className() = 0;
	virtual CVEHICLE* Clone() = 0;

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

	// Render method
	virtual void drawToConsole(int,int,Console&);

protected:
	static CVEHICLE* addSample(CVEHICLE*);
};

#endif // CVEHICLE_H
