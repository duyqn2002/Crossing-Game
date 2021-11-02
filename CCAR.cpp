#include"CCAR.h"


CCAR::CCAR()
{
	mVehicleLeftForm = "       _____  \n"
					   "  __../_||_|\\ \n"
					   " /_ _    _   `)\n"
				       "'-()--()-'=    ";

	/*mVehicleRightForm = "  ______      \n"
						" /|_ ||_\\`.__ \n"
						"(   _    _ _ \\\n"
						"   =`-()--()-'";*/

	mVehicleRightForm = "  _____       \n"
					    " /|_||_\\..__  \n"
					    "(`  _  _ _   \\\n"
						"   ='-()--()-'";

	mHeight = mVehicleLeftForm.Height();
	mWidth = mVehicleLeftForm.Width();

	mVehicleColour = CAR_COLOUR;
}

CCAR::CCAR(int x, int y, int left, int right) : CCAR() {
	setXY(x, y);
	setLimit(left, right);
}