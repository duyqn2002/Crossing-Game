#ifndef TRAFFIC_LIGHT_RED_H
#define	TRAFFIC_LIGHT_RED_H

#include "ITrafficLightState.h"

class TrafficLightRedState : public ITrafficLightState {
public:
	TrafficLightRedState(CLANE* , int = 5);

	void Timer();
	bool isStop();
	void drawTrafficLight(int , int , int , Console& );
};

#endif // TRAFFIC_LIGHT_RED_H


