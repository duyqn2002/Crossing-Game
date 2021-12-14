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

	mCurrVehicleForm = &mVehicleLeftForm;
	mVehicleColour = CAR_COLOUR;
}

CCAR::CCAR(const CCAR& other) {
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

CVEHICLE* CCAR::Clone() {
	return new CCAR(*this);
}