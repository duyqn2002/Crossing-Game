#include "CLANE.h"
#include "TrafficLightGreenState.h"

TrafficLightGreenState::TrafficLightGreenState(CLANE* Lane, int interval) {
	mLane = Lane;
	mStartTime = clock();
	mEndTime = clock();
	mInterval = interval;
}

void TrafficLightGreenState::Timer()
{
	mEndTime = clock();
	int duration = (mEndTime - mStartTime) / (double)CLOCKS_PER_SEC;
	if (duration >= mInterval) {
		ITrafficLightState* redLight = mLane->getRedLightState();
		redLight->setStartTime(mEndTime);
		mLane->setTrafficLightState(redLight);
	}
}

bool TrafficLightGreenState::isStop() {
	Timer();
	return false;
}

void TrafficLightGreenState::drawTrafficLight(int x, int y, int width, Console& console) {
	console.DrawPixels(x, y, ' ', COLOUR::GREEN_BG, width);
}