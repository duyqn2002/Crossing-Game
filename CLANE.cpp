#include "CLANE.h"

CLANE::CLANE(){
	mY = 0;
	mSpeedOnLane = 0;
	mLeftLimit = 0;
	mRightLimit = 0;
	mEnabledTrafficLight = false;

	mGreenLight = nullptr;
	mRedLight = nullptr;

	mCurrLightState = nullptr;
}

CLANE::CLANE(int left,int right) : CLANE() {
	setLimit(left, right);
}

CLANE::CLANE(const CLANE& other) : CLANE() {
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
			setTrafficLightState(mGreenLight);
		}
		else {
			setTrafficLightState(mRedLight);
		}
	}
	else {
		disableTrafficLight();
	}
}

CLANE::~CLANE() {
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

CLANE& CLANE::operator=(const CLANE& other)
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
			setTrafficLightState(mGreenLight);
		}
		else {
			setTrafficLightState(mRedLight);
		}
	}
	else {
		disableTrafficLight();
	}

	return *this;
}

Movable& CLANE::operator[](int pos){
	return (*mObjects[pos]);
}

const Movable& CLANE::operator[](int pos) const {
	return (*mObjects[pos]);
}

void CLANE::setY(int y)
{
	mY = y;
}

void CLANE::setLimit(int left, int right)
{
	mLeftLimit = left;
	mRightLimit = right;
}

void CLANE::setSpeed(int speed)
{
	mSpeedOnLane = speed;
}

void CLANE::setTrafficLightState(ITrafficLightState* state)
{
	mCurrLightState = state;
}

int CLANE::getY() const
{
	return mY;
}

int CLANE::size() const {
	return mObjects.size();
}

ITrafficLightState* CLANE::getTrafficLightState() {
	return mCurrLightState;
}

ITrafficLightState* CLANE::getRedLightState() {
	return mRedLight;
}

ITrafficLightState* CLANE::getGreenLightState() {
	return mGreenLight;
}

void CLANE::enableTrafficLight()
{
	mEnabledTrafficLight = true;

	// Go for 2s to 5s
	int randomIntervalLightTime = RandomInt(5, 2);
	if(mGreenLight == nullptr)
		mGreenLight = new TrafficLightGreenState(this, randomIntervalLightTime);

	// Stop for 1s to 3s
	randomIntervalLightTime = RandomInt(3, 1);
	if(mRedLight == nullptr)
		mRedLight = new TrafficLightRedState(this, randomIntervalLightTime);

	if(mCurrLightState == nullptr)
		mCurrLightState = mGreenLight;
}

void CLANE::disableTrafficLight()
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

void CLANE::updateObjectsOnLane()
{
	if (mEnabledTrafficLight) {
		if (mCurrLightState->isStop())
			return;
	}

	for (auto& object : mObjects) {
		int posX = object->getX();
		if (mSpeedOnLane > 0) {
			if (posX > mRightLimit)
				object->setXY(mLeftLimit - object->Width(),mY);
		}
		else {
			if (posX < mLeftLimit - object->Width())
				object->setXY(mRightLimit,mY);
		}
		object->Move(mSpeedOnLane,0);
	}
}

void CLANE::generateObjectsOnLane(const ENEMY& className, int numberOfObjects)
{
	Movable* Object = CEnemyFactory::createEneny(className);
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
		randomX = right - RandomInt(laneWidth / 5, Object->Width());
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
		int randomGap = RandomInt(Object->Width() + 50, Object->Width());

		Movable* tempItem = Object->Clone();
		if (mSpeedOnLane > 0) {
			tempItem->setXY(mObjects[i - 1]->getX() - randomGap, mY);
		}
		else {
			tempItem->setXY(mObjects[i - 1]->getX() + randomGap, mY);

		}
		mObjects.push_back(tempItem);
	}
}

void CLANE::drawTrafficLight(Console& console)
{
	int width = 2;
	int trafficLightPosX = (mSpeedOnLane > 0) ? mRightLimit - width : mLeftLimit + 1;
	mCurrLightState->drawTrafficLight(trafficLightPosX, mY, width, console);
}

void CLANE::drawObjectsOnLane(Console& console)
{
	for (auto& item : mObjects) {
		item->drawToConsole(console,mLeftLimit,mRightLimit );
	}

	if (mEnabledTrafficLight) {
		drawTrafficLight(console);
	}
}
