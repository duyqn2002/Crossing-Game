#include "HelpFunctions.h"

#ifndef CANIMAL_H
#define CANIMAL_H

class CANIMAL {
	int mX, mY;
public:
	virtual void Move(int, int);
	virtual void Tell();
};

#endif // CANIMAL_H
