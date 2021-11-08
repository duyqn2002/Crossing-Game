#include "CDOG.h"

CDOG::CDOG() {
	mCurrPos = CPOINT2D(0, 0);

	mAnimalLeftForm = "  __      _\n"
					"o'')}____//\n"
					" `_/      )\n"
					" (_(_/-(_/\n";

	mAnimalRightForm = "_      __  \n"
					"\\\____{(''o\n"
					"(       \\_' \n"
					"\\_)-\\\_)_)\n";

	mHeight = mAnimalLeftForm.Height();
	mWidth = mAnimalLeftForm.Width();

	mSpeed = 0;

	mCurrAnimalForm = &mAnimalLeftForm;
	mAnimalColour = DOG_COLOUR;
}

CDOG::CDOG(const CDOG& other) {
	// Current position
	mCurrPos = other.mCurrPos;

	// Width and height of animal
	mHeight = other.mHeight;
	mWidth = other.mWidth;

	// Limit left and right X
	mLeft = other.mLeft;
	mRight = other.mRight;

	// Speed of animal
	mSpeed = other.mSpeed;

	// Animal form
	mAnimalLeftForm = other.mAnimalLeftForm;
	mAnimalRightForm = other.mAnimalRightForm;

	// Assign pointer
	if (other.mCurrAnimalForm == &other.mAnimalLeftForm) {
		mCurrAnimalForm = &mAnimalLeftForm;
	}
	else {
		mCurrAnimalForm = &mAnimalRightForm;
	}

	// Color for animal
	mAnimalColour = other.mAnimalColour;
}