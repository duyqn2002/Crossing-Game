#ifndef TRAFFIC_LIGHT_GREEN_H
#define	TRAFFIC_LIGHT_GREEN_H

#include "ITrafficLightState.h"

template <class T>
class TrafficLightGreenState : public ITrafficLightState {
private:
	CLANE<T>* mLane;
	clock_t mStartTime;
	clock_t mEndTime;
	int mInterval;
public:
	TrafficLightGreenState(CLANE<T>* Lane, int interval = 5) {
		mLane = Lane;
		mStartTime = clock();
		mEndTime = clock();
		mInterval = interval;
	}

	void setStartTime(clock_t startTime) {
		mStartTime = startTime;
	}

	void Timer();
	bool isStop() {
		Timer();
		return false;
	}
	void drawTrafficLight(int x, int y, int width, Console& console) {
		console.DrawPixels(x, y, ' ', COLOUR::GREEN_BG, width);

	}
};

#endif // TRAFFIC_LIGHT_GREEN_H


