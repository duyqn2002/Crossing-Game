#ifndef CLANE_H
#define CLANE_H

#include "HelpFunctions.h"
#include "CVEHICLE.h"
#include "CANIMAL.h"

#include "TrafficLightGreenState.h"
#include "TrafficLightRedState.h"

template <class ObjectType>
class CLANE {
private:
	int mY;
	int mSpeedOnLane;
	int mLeftLimit;
	int mRightLimit;

	std::vector<ObjectType*> mObjects;

	bool mEnabledTrafficLight;

	ITrafficLightState* mGreenLight;
	ITrafficLightState* mRedLight;
	ITrafficLightState* mCurrLightState;
public:
	CLANE();
	CLANE(int, int);
	CLANE(const CLANE&);
	~CLANE();

	// Operator overloading
	CLANE& operator= (const CLANE&);
	ObjectType& operator[](int);
	const ObjectType& operator[](int) const;

	// Setter
	void setY(int);
	void setLimit(int, int);
	void setSpeed(int);
	void setTrafficLightState(ITrafficLightState*);

	// Getter
	int getY() const;
	int getLimitLeft();
	int getSpeed() const;
	int size() const;
	ITrafficLightState* getTrafficLightState();
	ITrafficLightState* getRedLightState();
	ITrafficLightState* getGreenLightState();

	// Method
	void enableTrafficLight();
	void disableTrafficLight();

	void generateObjectsOnLane(const ENEMY&,int);
	void updateObjectsOnLane();
	void drawTrafficLight(Console&);
	void drawObjectsOnLane(Console&);
};

template<class T>
void TrafficLightGreenState<T>::Timer()
{
	mEndTime = clock();
	int duration = (mEndTime - mStartTime) / (double)CLOCKS_PER_SEC;
	if (duration == mInterval) {
		ITrafficLightState* redLight = mLane->getRedLightState();
		redLight->setStartTime(mEndTime);
		mLane->setTrafficLightState(redLight);
	}
}

template<class T>
void TrafficLightRedState<T>::Timer()
{
	mEndTime = clock();
	int duration = (mEndTime - mStartTime) / (double)CLOCKS_PER_SEC;
	if (duration == mInterval) {
		ITrafficLightState* greenLight = mLane->getGreenLightState();
		greenLight->setStartTime(mEndTime);
		mLane->setTrafficLightState(greenLight);
	}
}

#endif // CLANE_H
