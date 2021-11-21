#ifndef CTRUCK_H
#define CTRUCK_H

#include "CVEHICLE.h"

class CTRUCK : public CVEHICLE {
public:
	CTRUCK();
	CTRUCK(const CTRUCK&);
	virtual CVEHICLE* Clone();
};

#endif // CTRUCK_H