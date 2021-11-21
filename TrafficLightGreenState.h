#ifndef TRAFFIC_LIGHT_GREEN_H
#define	TRAFFIC_LIGHT_GREEN_H

#include "ITrafficLightState.h"

class TrafficLightGreenState : public ITrafficLightState {
public:
	TrafficLightGreenState(CLANE* , int  = 5);
	virtual void setStartTime(clock_t);
	virtual void Timer();
	virtual bool isStop(); 
	virtual void drawTrafficLight(int , int , int , Console& );
};

#endif // TRAFFIC_LIGHT_GREEN_H


