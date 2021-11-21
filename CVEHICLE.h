#ifndef CVEHICLE_H
#define CVEHICLE_H

#include "Console.h"
#include "Movable.h"

class CVEHICLE : public Movable{
protected:
	// Current position
	CPOINT2D mCurrPos;

	// Width and height of vehicle
	int mHeight;
	int mWidth;

	// Vehicle form
	Texture mVehicleLeftForm;
	Texture mVehicleRightForm;
	Texture* mCurrVehicleForm;

	// Color for vehicle
	COLOUR mVehicleColour;
public:
	CVEHICLE() = default;
	virtual ~CVEHICLE() = default;
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
	virtual void drawToConsole(Console&, int, int);
};

#endif // CVEHICLE_H
