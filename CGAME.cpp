#include "CGAME.h"

CGAME::CGAME()  {
	mConsole = Console(WINDOW_BUFFER_WIDTH, WINDOW_BUFFER_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
	// Set obj
	setPlayingArea(SCALE_X, SCALE_Y);
	setObject();
	setPeople();
}

CGAME* CGAME::m_pGame = nullptr;

CGAME* CGAME::getGame() {
	if (m_pGame == nullptr)
		m_pGame = new CGAME();
	return m_pGame;
}

CGAME::~CGAME() {
	for (auto& lane : m_vecVehicles) {
		for (auto& vehicle : lane.second) {
			delete vehicle;
			vehicle = nullptr;
		}
	}

	for (auto& lane : m_vecAnimals) {
		for (auto& animal : lane.second) {
			delete animal;
			animal = nullptr;
		}
	}
}

template <class T>
bool isSamePos(vector<T*> vecObjects, T* inObject) {
	for (auto& Object : vecObjects) {
		if (Object == inObject)
			continue;
		if (Object->isImpact(*inObject) == true)
			return true;
	}

	return false;
}

template <class T>
vector<T*> createObjects(T* Object,int numberOfVehicles) {
	vector<T*> vecObjects;
	int left = Object->getLeft();
	int right = Object->getRight();


	int width = Object->Width();
	int randomGap = 0;


	// If the template Object == nullptr return empty vector
	if (Object != nullptr) {
		// Push back to the vector
		vecObjects.push_back(Object);

		for (int index = 1; index < numberOfVehicles; index++) {
			// Cloning Technique
			T* tempObj = Object->Clone();
			int prevObjPosX = vecObjects[index - 1]->getX();

			randomGap = RandomInt(50, width);

			tempObj->setX(prevObjPosX + randomGap);

			vecObjects.push_back(tempObj);
		}
	}

	return vecObjects;
}


void CGAME::setObject() {
	int left = mTopLeft.getX();
	int right = mBottomRight.getX();

	int x;
	int y = mTopLeft.getY() + 1;

	CVEHICLE* vehicle;
	CANIMAL* animal;

	for (const auto& lane : m_vecLanes) {
		int randomQty = RandomInt(3, 2);

		vehicle = CVEHICLE::createObject(lane.second);
		animal = CANIMAL::createObject(lane.second);

		do {
			x = RandomInt(right + 50, left); - 50;
		} while (x > left && x < right);

		if (vehicle != nullptr) {
			vehicle->setXY(x, y);
			vehicle->setSpeed(lane.first);
			vehicle->setLimit(left, right);
			m_vecVehicles.push_back({ y, createObjects(vehicle, randomQty) });

		}

		if (animal != nullptr) {
			animal->setXY(x, y);
			animal->setSpeed(lane.first);
			animal->setLimit(left, right);
			m_vecAnimals.push_back({ y, createObjects(animal,randomQty)});
		}

		y += LANE_SIZE;
	}
}

void CGAME::setPeople() {
	// Set the position of people
	// Generate randomly X by multiplying a floating number between 0.2 to 0.8
	float randomPercent = (float) RandomInt(8, 2) / 10.0f;
	int x = mBottomRight.getX() - mTopLeft.getX();
	int y = mBottomRight.getY() - mPeople.Height();

	// X is random, Y must at the end of the last square
	x = x * randomPercent;
	mPeople = CPEOPLE(x, y, mTopLeft, mBottomRight);
}

void CGAME::setPlayingArea(float scaleX,float scaleY) {
	// Set the size of the playing area
	int mPlayingAreaHeight = mConsole.Height() * scaleY - 1;
	int mPlayingAreaWdth = mConsole.Width() * scaleX - 1;

	// Set the top left point of the playing area
	mTopLeft = CPOINT2D(TOP_LEFT_X, TOP_LEFT_Y);
	mBottomRight = CPOINT2D(TOP_LEFT_X + mPlayingAreaWdth, TOP_LEFT_Y + mPlayingAreaHeight);
}

CPEOPLE CGAME::getPeople() const {
	return mPeople;
}

vector<CVEHICLE*> CGAME::getVehicles() const{

	return vector<CVEHICLE*>();
}

vector<CANIMAL*> CGAME::getAnimals() const{
	return vector<CANIMAL*>();
}

void CGAME::drawPlayingArea()  const {
	// Draw the border line
	mConsole.DrawBorder(mTopLeft, mBottomRight, PLAYING_AREA_COLOUR);
}

void  CGAME::drawVehicles() const {
	for (const auto& vehicleLane : m_vecVehicles) {
		for (const auto& vehicle : vehicleLane.second) {
			vehicle->drawVehicle(mConsole);
		}
	}
}

void  CGAME::drawAnimals() const {
	for (const auto& animalLane : m_vecAnimals) {
		for (const auto& animal : animalLane.second) {
			animal->drawAnimal(mConsole);
		}
	}
}

void CGAME::drawGame() {
	// Clear the old screen
	mConsole.ClearScreen();

	// Draw border
	drawPlayingArea();

	// Draw people
	mPeople.drawPeople(mConsole);

	//// Draw object
	drawVehicles();
	drawAnimals();

	// Render out console
	mConsole.Render();
}

void CGAME::resetGame() {
	if (m_pGame != nullptr) {
		delete m_pGame;
		m_pGame = new CGAME();
	}
}

void CGAME::startGame() {
	resetGame();
}

void CGAME::loadGame(istream) {}

void CGAME::saveGame(istream) {}

void CGAME::pauseGame(HANDLE handleThread) const {
	SuspendThread(handleThread);
}

void CGAME::resumeGame(HANDLE handleThread) const {
	ResumeThread(handleThread);
}

void CGAME::exitGame(HANDLE handleThread) {

}

void CGAME::updatePosPeople(DIRECTION direction) {
	mPeople.Move(direction,LANE_SIZE);
}

void CGAME::updatePosVehicle() {
	for (auto& vehicleLane : m_vecVehicles) {
		for (auto& vehicle : vehicleLane.second) {
			vehicle->updatePos();
		}
	}
}

void CGAME::updatePosAnimal() {
	for (auto& animalLane : m_vecAnimals) {
		for (auto& animal : animalLane.second) {
			animal->updatePos();
		}
	}
}
