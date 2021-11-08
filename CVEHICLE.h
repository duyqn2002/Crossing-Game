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

	// Limit left and right X
	int mLeft = 0;
	int mRight = 0;

	// Speed of vehicle
	double mSpeed;

	// Vehicle form
	Texture mVehicleLeftForm;
	Texture mVehicleRightForm;
	Texture* mCurrVehicleForm;

	// Color for vehicle
	COLOUR mVehicleColour = DEFAULT_COLOUR;

public:
	CVEHICLE() = default;
	virtual ~CVEHICLE() = default;

	static CVEHICLE* createObject(const string&);

	virtual string className() = 0;
	virtual CVEHICLE* Clone() = 0;

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

	// Check impact with another vehicle
	bool isImpact(const CVEHICLE&) const;

	// Update method
	void toggleForm();
	void Move(int, int);
	void resetPos();
	void updatePos();

	// Render method
	void drawVehicle(const Console&) const;

protected:
	static CVEHICLE* addSample(CVEHICLE*);
};

#endif // CVEHICLE_H
