#ifndef CALIEN_SHIP_H
#define CALIEN_SHIP_H

#include "CVEHICLE.h"
#include "CPEOPLE.h"

class CAlienShip : public CVEHICLE
{
private:
	int mPosXOfPeople;
	int mPosYOfPeople;
public:
	CAlienShip();
	CAlienShip(const CAlienShip&);
	virtual CVEHICLE* Clone();

	void setPeoplePos(int, int);
	bool isCapturePeople() const;
	void updatePos();
};

#endif // !CALIEN_SHIP_H


