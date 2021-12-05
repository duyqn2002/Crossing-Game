#ifndef CDOG_H
#define CDOG_H

#include "CANIMAL.h"

class CDOG : public CANIMAL {
public:
	CDOG();
	CDOG(const CDOG&);
	virtual CANIMAL* Clone();
	virtual void Tell();
};

#endif // CDOG_H

