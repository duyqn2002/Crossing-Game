#include"CCAR.h"

CCAR::CCAR()
{
	mCurrPos = CPOINT2D(0, 0);

	mVehicleLeftForm = "       _____  \n"
					   "  __../_||_|\\ \n"
					   " /_ _    _   `)\n"
				       "'-()--()-'=    ";

	mVehicleRightForm = "  _____       \n"
					    " /|_||_\\..__  \n"
					    "(`  _  _ _   \\\n"
						"   ='-()--()-'";

	mHeight = mVehicleLeftForm.Height();
	mWidth = mVehicleLeftForm.Width();

	mSpeed = 0;

	mCurrVehicleForm = &mVehicleLeftForm;
	mVehicleColour = CAR_COLOUR;
}

CCAR::CCAR(const CCAR& other) {
	// Current position
	mCurrPos = other.mCurrPos;

	// Width and height of vehicle
	mHeight = other.mHeight;
	mWidth = other.mWidth;

	// Limit left and right X
	mLeft = other.mLeft;
	mRight = other.mRight;

	// Speed of vehicle
	mSpeed = other.mSpeed;

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