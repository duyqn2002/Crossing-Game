#include"CBIRD.h"

CBIRD::CBIRD()
{
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

	mAnimalColour = BIRD_COLOUR;
}

CBIRD::CBIRD(int x, int y, int left, int right) : CBIRD() {
	setXY(x, y);
	setLimit(left, right);
}