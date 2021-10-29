#include "CTRUCK.h"

CTRUCK::CTRUCK() {
	mVehicleLeftForm = "   __   ________ \n"
					   " _//]| |        |\n"
					   "|____|-|________|\n"
					   "   O     O    O    ";

	mVehicleRightForm = " ________   __   \n"
						"|        | |[\\\\_ \n"
						"|________|-|____| \n"
				   	    "  O   O      O   ";

	mHeight = GetHeightAsciiArt(mVehicleLeftForm);
	mWidth = GetWidthAsciiArt(mVehicleLeftForm);

	mVehicleColour = TRUCK_COLOUR;
}
