#ifndef CTRUCK_H
#define CTRUCK_H

#include "CVEHICLE.h"

class CTRUCK : public CVEHICLE {
private:
	INIT_MEMBER(CVEHICLE,CTRUCK);
public:
	CTRUCK();
	CTRUCK(const CTRUCK&);

	INIT_METHOD(CVEHICLE,CTRUCK);
};

#endif // CTRUCK_H