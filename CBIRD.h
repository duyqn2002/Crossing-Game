#ifndef CBIRD_H
#define CBIRD_H

#include"CANIMAL.h"

class CBIRD : public CANIMAL {
public:
	CBIRD();
	CBIRD(const CBIRD&);
	virtual CANIMAL* Clone();
	virtual void Tell();
};


#endif // CBIRD_H