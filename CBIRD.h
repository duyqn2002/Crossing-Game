#ifndef CBIRD_H
#define CBIRD_H

#include"CANIMAL.h"

class CBIRD : public CANIMAL {
private:
	INIT_MEMBER(CANIMAL, CBIRD);
public:
	CBIRD();
	CBIRD(const CBIRD&);
	INIT_METHOD(CANIMAL, CBIRD);
};


#endif // CBIRD_H