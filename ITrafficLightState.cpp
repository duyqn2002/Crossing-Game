#include "ITrafficLightState.h"

void ITrafficLightState::setInterval(int interval)
{
	if(interval > 0)
		mInterval = interval;
}

void ITrafficLightState::setStartTime(clock_t startTime)
{
	mStartTime = startTime;
}

int ITrafficLightState::getInterval() const
{
	return mInterval;
}


