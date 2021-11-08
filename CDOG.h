#ifndef CDOG_H
#define CDOG_H

#include "CANIMAL.h"

class CDOG : public CANIMAL {
private:
	INIT_MEMBER(CANIMAL, CDOG);
public:
	CDOG();
	CDOG(const CDOG&);

	INIT_METHOD(CANIMAL, CDOG);
};

#endif // CDOG_H

