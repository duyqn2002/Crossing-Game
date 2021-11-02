#include "CGAME.h"

CGAME::CGAME()  {
	m_Console = Console(WINDOW_BUFFER_WIDTH, WINDOW_BUFFER_HEIGHT, FONT_WIDTH, FONT_HEIGHT);

	// Set obj
	setPlayingArea();
	setLanes();
	setPeople();
}

CGAME* CGAME::m_pGame = nullptr;

CGAME* CGAME::getGame() {
	if (m_pGame == nullptr)
		m_pGame = new CGAME();
	return m_pGame;
}

void CGAME::setLanes() {
	for (int i = 0; i < MAX_LANE; i++) {
		vector<CVEHICLE*> vehicleInLane;
		int randomQty = RandomInt(5, 3);
		int y = i * LANE_SIZE + 1;

		for (int j = 0; j < 1; j++) {
			int randomX = RandomInt(mBottomRight.getX(), mTopLeft.getX());
			CVEHICLE* truck = new CTRUCK(0,y, mTopLeft.getX(), mBottomRight.getX());
			truck->setSpeed(-1);
			vehicleInLane.push_back(truck);
		}
		m_vecVehicles.push_back({ y,vehicleInLane });
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

void CGAME::setPlayingArea() {
	// Set the size of the playing area
	int mPlayingAreaHeight = WINDOW_BUFFER_HEIGHT * SCALE_Y - 1;
	int mPlayingAreaWdth = WINDOW_BUFFER_WIDTH * SCALE_X - 1;

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

void CGAME::drawPlayingArea()  {
	// Draw the border line
	m_Console.DrawBorder(mTopLeft, mBottomRight, PLAYING_AREA_COLOUR);
}

void  CGAME::drawVehicles()  {
	for (const auto& vehicleLane : m_vecVehicles) {
		for (const auto& vehicle : vehicleLane.second) {
			vehicle->drawVehicle(m_Console);
		}
	}
}

void  CGAME::drawAnimals() {}

void CGAME::drawGame()  {
	m_Console.ClearScreen();

	drawPlayingArea();
	// Draw people
	mPeople.drawPeople(m_Console);

	//// Draw object
	drawVehicles();
	//drawAnimals();
	m_Console.Render();
}

void CGAME::resetGame() {
	if (m_pGame != nullptr) {
		delete m_pGame;
		m_pGame = new CGAME();
	}
}


void CGAME::startGame() {
	drawPlayingArea();
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
	vector<pair<float, string>>::iterator i = m_vecLanes.begin();
	for (auto vehicleLane : m_vecVehicles) {
		for (auto vehicle : vehicleLane.second) {
			vehicle->updatePos();
			i++;
		}
	}
}

void CGAME::updatePosAnimal() {
}

bool CGAME::isRunning() const {
	return mIsRunning;
}