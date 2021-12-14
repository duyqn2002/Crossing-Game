#include "HelpFunctions.h"

int RandomInt(int MAX, int MIN) {
	random_device randDevice;
	int range = MAX - MIN + 1;
	return randDevice() % range + MIN;
}