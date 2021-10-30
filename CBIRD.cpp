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

	mHeight = GetHeightAsciiArt(mAnimalLeftForm);
	mWidth = GetWidthAsciiArt(mAnimalLeftForm);

	mAnimalColour = BIRD_COLOUR;
}