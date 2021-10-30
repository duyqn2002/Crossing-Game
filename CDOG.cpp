#include"CDOG.h"

CDOG::CDOG()
{
	mAnimalLeftForm = "  __      _\n"
					  "o'')}____//\n"
	               	  " `_/      )\n"
	                  " (_(_/-(_/\n";

	mAnimalRightForm = "_      __  \n"
		               "\\\____{(''o\n"
		               "(       \\_' \n"
		               "\\_)-\\\_)_)\n";

	mHeight = GetHeightAsciiArt(mAnimalLeftForm);
	mWidth = GetWidthAsciiArt(mAnimalLeftForm);

	mAnimalColour = DOG_COLOUR;
}