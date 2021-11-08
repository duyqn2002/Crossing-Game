#ifndef CCAR_H
#define CCAR_H

#include "CVEHICLE.h"

class CCAR : public CVEHICLE {
private:
	INIT_MEMBER(CVEHICLE, CCAR);
public:
	CCAR();
	CCAR(const CCAR&);

	INIT_METHOD(CVEHICLE, CCAR);
};

#endif // CCAR_H

