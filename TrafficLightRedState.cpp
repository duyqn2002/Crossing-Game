#include "CLANE.h"
#include "TrafficLightRedState.h"

TrafficLightRedState::TrafficLightRedState(CLANE* Lane, int interval) {
	mLane = Lane;
	mStartTime = clock();
	mEndTime = clock();
	mInterval = interval;
}

void TrafficLightRedState::setStartTime(clock_t startTime) {
	mStartTime = startTime;
}

void TrafficLightRedState::Timer()
{
	mEndTime = clock();
	int duration = (mEndTime - mStartTime) / (double)CLOCKS_PER_SEC;
	if (duration >= mInterval) {
		ITrafficLightState* greenLight = mLane->getGreenLightState();
		greenLight->setStartTime(mEndTime);
		mLane->setTrafficLightState(greenLight);
	}
}

bool TrafficLightRedState::isStop() {
	Timer();
	return true;
}
void TrafficLightRedState::drawTrafficLight(int x, int y, int width, Console& console) {
	console.DrawPixels(x, y, ' ', COLOUR::RED_BG, width);
}