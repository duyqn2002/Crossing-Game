#include "CDOG.h"

CDOG::CDOG() {
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

	mAnimalColour = DOG_COLOUR;
}

CDOG::CDOG(int x, int y, int left, int right) {
	setXY(x, y);
	setLimit(left, right);
}