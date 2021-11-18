#include "CLANE.h"

template <class ObjectType>
CLANE<ObjectType>::CLANE(){
	mY = 0;
	mSpeedOnLane = 0;
	mLeftLimit = 0;
	mRightLimit = 0;
	mEnabledTrafficLight = false;

	mGreenLight = nullptr;
	mRedLight = nullptr;

	mCurrLightState = nullptr;
}

template <class ObjectType>
CLANE<ObjectType>::CLANE(int left,int right) : CLANE<ObjectType>() {
	setLimit(left, right);
}

template<class ObjectType>
CLANE<ObjectType>::CLANE(const CLANE<ObjectType>& other) : CLANE<ObjectType>() {
	mObjects.resize(0);
	for (auto& object : other.mObjects) {
		mObjects.push_back(object->Clone());
	}

	mY = other.mY;
	mLeftLimit = other.mLeftLimit;
	mRightLimit = other.mRightLimit;
	mSpeedOnLane = other.mSpeedOnLane;
	mEnabledTrafficLight = other.mEnabledTrafficLight;

	if (mEnabledTrafficLight) {
		enableTrafficLight();
		if (other.mCurrLightState == other.mGreenLight) {
			mCurrLightState = mGreenLight;
		}
		else {
			mCurrLightState = mRedLight;
		}
	}
	else {
		disableTrafficLight();
	}
}

template <class ObjectType>
CLANE<ObjectType>::~CLANE() {
	for (auto& object : mObjects) {
		delete object;
		object = nullptr;
	}

	if (mGreenLight != nullptr) {
		delete mGreenLight;
		mGreenLight = nullptr;
	}

	if (mRedLight != nullptr) {
		delete mRedLight;
		mRedLight = nullptr;
	}

	mCurrLightState = nullptr;
}

template<class ObjectType>
CLANE<ObjectType>& CLANE<ObjectType>::operator=(const CLANE<ObjectType>& other)
{
	if (this == &other)
		return *this;

	// Erase the old items
	for (auto& object : mObjects) {
		delete object;
		object = nullptr;
	}
	mObjects.clear();

	// Assign the copy
	for (auto& object : other.mObjects) {
		mObjects.push_back(object->Clone());
	}

	mY = other.mY;
	mLeftLimit = other.mLeftLimit;
	mRightLimit = other.mRightLimit;
	mSpeedOnLane = other.mSpeedOnLane;
	mEnabledTrafficLight = other.mEnabledTrafficLight;

	mGreenLight = nullptr;
	mRedLight = nullptr;

	mCurrLightState = nullptr;

	if (mEnabledTrafficLight) {
		enableTrafficLight();
		if (other.mCurrLightState == other.mGreenLight) {
			mCurrLightState = mGreenLight;
		}
		else {
			mCurrLightState = mRedLight;
		}
	}
	else {
		disableTrafficLight();
	}

	return *this;
}

template<class ObjectType>
ObjectType& CLANE<ObjectType>::operator[](int pos){
	return (*mObjects[pos]);
}

template<class ObjectType>
const ObjectType& CLANE<ObjectType>::operator[](int pos) const {
	return (*mObjects[pos]);
}

template<class ObjectType>
void CLANE<ObjectType>::setY(int y)
{
	mY = y;
}

template<class ObjectType>
void CLANE<ObjectType>::setLimit(int left, int right)
{
	mLeftLimit = left;
	mRightLimit = right;
}

template<class ObjectType>
void CLANE<ObjectType>::setSpeed(int speed)
{
	mSpeedOnLane = speed;
}

template<class ObjectType>
void CLANE<ObjectType>::setTrafficLightState(ITrafficLightState* state)
{
	mCurrLightState = state;
}

template<class ObjectType>
int CLANE<ObjectType>::getY() const
{
	return mY;
}

template<class ObjectType>
int CLANE<ObjectType>::size() const {
	return mObjects.size();
}

template<class ObjectType>
ITrafficLightState* CLANE<ObjectType>::getTrafficLightState() {
	return mCurrLightState;
}

template<class ObjectType>
ITrafficLightState* CLANE<ObjectType>::getRedLightState() {
	return mRedLight;
}

template<class ObjectType>
ITrafficLightState* CLANE<ObjectType>::getGreenLightState() {
	return mGreenLight;
}

template<class ObjectType>
void CLANE<ObjectType>::enableTrafficLight()
{
	mEnabledTrafficLight = true;

	// Go for 2s to 5s
	int randomIntervalLightTime = RandomInt(5, 2);
	if(mGreenLight == nullptr)
		mGreenLight = new TrafficLightGreenState<ObjectType>(this, randomIntervalLightTime);

	// Stop for 1s to 3s
	randomIntervalLightTime = RandomInt(3, 1);
	if(mRedLight == nullptr)
		mRedLight = new TrafficLightRedState<ObjectType>(this, randomIntervalLightTime);

	if(mCurrLightState == nullptr)
		mCurrLightState = mGreenLight;
}

template<class ObjectType>
void CLANE<ObjectType>::disableTrafficLight()
{
	mEnabledTrafficLight = false;

	if (mGreenLight != nullptr) {
		delete mGreenLight;
		mGreenLight = nullptr;
	}

	if (mRedLight != nullptr) {
		delete mRedLight;
		mRedLight = nullptr;
	}

	mCurrLightState = nullptr;
}

template<class ObjectType>
void CLANE<ObjectType>::updateObjectsOnLane()
{
	if (mEnabledTrafficLight) {
		if (mCurrLightState->isStop())
			return;
	}

	for (auto& object : mObjects) {
		int posX = object->getX();
		if (mSpeedOnLane > 0) {
			if (posX > mRightLimit)
				object->setX(mLeftLimit - object->Width());
		}
		else {
			if (posX < mLeftLimit - object->Width())
				object->setX(mRightLimit);
		}
		object->Move(mSpeedOnLane,0);
	}
}

template<class ObjectType>
void CLANE<ObjectType>::generateObjectsOnLane(const ENEMY& className, int numberOfObjects)
{
	ObjectType* Object = ObjectType::createObject(className);
	if (Object == nullptr)
		return;

	if (numberOfObjects <= 0)
		return;

	int left = mLeftLimit;
	int right = mRightLimit;
	int laneWidth = right - left;
	int randomX;

	if (mSpeedOnLane > 0) {
		right = left;
		left -= laneWidth;
		randomX = right - RandomInt(laneWidth / 5, 1);
	}
	else {
		left = right;
		right += laneWidth;
		randomX = left + RandomInt(laneWidth / 5, 1);
	}

	Object->setXY(randomX, mY);
	Object->toggleForm(mSpeedOnLane);
	mObjects.push_back(Object);

	for (int i = 1; i < numberOfObjects; i++) {
		randomX = RandomInt(Object->Width() + 50, Object->Width());

		ObjectType* tempItem = Object->Clone();
		if (mSpeedOnLane > 0) {
			tempItem->setX(mObjects[i - 1]->getX() - randomX);
		}
		else {
			tempItem->setX(mObjects[i - 1]->getX() + randomX);

		}
		mObjects.push_back(tempItem);
	}
}

template<class ObjectType>
void CLANE<ObjectType>::drawTrafficLight(Console& console)
{
	int width = 2;
	int trafficLightPosX = (mSpeedOnLane > 0) ? mRightLimit - width : mLeftLimit + 1;
	mCurrLightState->drawTrafficLight(trafficLightPosX, mY, width, console);
}

template<class ObjectType>
void CLANE<ObjectType>::drawObjectsOnLane(Console& console)
{
	for (auto& item : mObjects) {
		item->drawToConsole(mLeftLimit,mRightLimit, console);
	}

	if (mEnabledTrafficLight) {
		drawTrafficLight(console);
	}
}

// Declare template
template class CLANE<CVEHICLE>;
template class CLANE<CANIMAL>;
template class TrafficLightGreenState<CVEHICLE>;
template class TrafficLightGreenState<CANIMAL>;
template class TrafficLightRedState<CVEHICLE>;
template class TrafficLightRedState<CANIMAL>;





