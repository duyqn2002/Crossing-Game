#include "CAlienShip.h"

CAlienShip::CAlienShip()
{
	mCurrPos = CPOINT2D(0, 0);

	mVehicleLeftForm = \
				"     ___\n"
				" ___/   \\___\n"
				"/   '---'   \\\n"
				"'--_______--'";
	mVehicleRightForm =  \
				"     ___\n"
				" ___/   \\___\n"
				"/   '---'   \\\n"
				"'--_______--'";

	mHeight = mVehicleRightForm.Height();
	mWidth = mVehicleRightForm.Width();

	mCurrVehicleForm = &mVehicleLeftForm;
	mVehicleColour = TRUCK_COLOUR;
}

CAlienShip::CAlienShip(const CAlienShip& other)
{
	// Current position
	mCurrPos = other.mCurrPos;

	// Width and height of vehicle
	mHeight = other.mHeight;
	mWidth = other.mWidth;

	// Vehicle form
	mVehicleLeftForm = other.mVehicleLeftForm;
	mVehicleRightForm = other.mVehicleRightForm;

	// Assign pointer
	if (other.mCurrVehicleForm == &other.mVehicleLeftForm) {
		mCurrVehicleForm = &mVehicleLeftForm;
	}
	else {
		mCurrVehicleForm = &mVehicleRightForm;
	}

	// Color for vehicle
	mVehicleColour = other.mVehicleColour;
}

CVEHICLE* CAlienShip::Clone()
{
	return new CAlienShip(*this);
}

void CAlienShip::setPeoplePos(int x, int y)
{
	mPosXOfPeople = x;
	mPosYOfPeople = y;
}

bool CAlienShip::isCapturePeople() const
{
	if(getX() != mPosXOfPeople || getY() != mPosYOfPeople) {
		return false;
	}
	return true;
}

void CAlienShip::updatePos()
{
	int x = getX();
	int y = getY();

	if (x > mPosXOfPeople) {
		x--;
	}
	else {
		if (x < mPosXOfPeople) {
			x++;
		}
	}

	if (y > mPosYOfPeople) {
		y--;
	}
	else {
		if (y < mPosYOfPeople) {
			y++;
		}
	}

	mCurrPos.setXY(x, y);
}

