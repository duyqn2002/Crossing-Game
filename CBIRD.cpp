#include"CBIRD.h"

CBIRD::CBIRD() {
	mCurrPos = CPOINT2D(0, 0);

	mAnimalLeftForm = " ,_ \n"
		">' )\n"
		"( ( \\\n"
		"mrf''|\\n";

	mAnimalRightForm = " _. \n"
		"( '<\n"
		"/ ) )\n"
		"/|''jnm\n";

	mHeight = mAnimalLeftForm.Height();
	mWidth = mAnimalLeftForm.Width();

	mSpeed = 0;

	mCurrAnimalForm = &mAnimalLeftForm;

	mAnimalColour = BIRD_COLOUR;
}

CBIRD::CBIRD(const CBIRD& other) {
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
