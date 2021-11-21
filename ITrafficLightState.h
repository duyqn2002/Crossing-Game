#ifndef ITRAFFIC_LIGHT_STATE_H
#define	ITRAFFIC_LIGHT_STATE_H

#include "Console.h"
#include <ctime>

class CLANE;

class ITrafficLightState {
protected:
	CLANE* mLane;
	clock_t mStartTime;
	clock_t mEndTime;
	int mInterval;

public:
	virtual void setStartTime(clock_t) = 0;
	virtual void Timer() = 0;
	virtual bool isStop() = 0;
	virtual void drawTrafficLight(int,int,int,Console&) = 0;
};

#endif // ITRAFFIC_LIGHT_STATE_H
