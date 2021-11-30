#ifndef CALIEN_SHIP_H
#define CALIEN_SHIP_H

#include "CVEHICLE.h"
#include "CPEOPLE.h"

class CAlienShip : public CVEHICLE
{
private:
	CPEOPLE* mPeople;
	unsigned int mSpeed;
	bool mIsReachPeople;
	bool mIsCapture;
public:
	CAlienShip();
	CAlienShip(const CAlienShip&);
	virtual CVEHICLE* Clone();

	void setPeople(CPEOPLE*);
	bool isReachPeople() const;
	bool isCapturePeople() const;
	void updatePos();
};

#endif // !CALIEN_SHIP_H


