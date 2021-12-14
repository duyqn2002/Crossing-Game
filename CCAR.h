#ifndef CCAR_H
#define CCAR_H

#include "CVEHICLE.h"

class CCAR : public CVEHICLE {
public:
	CCAR();
	CCAR(const CCAR&);
	virtual CVEHICLE* Clone();
};

#endif // CCAR_H

