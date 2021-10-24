#include "CVEHICLE.h"

#ifndef CTRUCK_H
#define CTRUCK_H

class CTRUCK : public CVEHICLE {
public:
	CTRUCK();
	char getName() const { return 'B'; }
	void drawVehicle();
};

#endif // CTRUCK_H