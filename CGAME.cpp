#include "CGAME.h"

void CGAME::setPeople() {
	// Set the position of people
	// Generate randomly X by multiplying a floating number between 0.2 to 0.8
	float randomPercent = RandomInt(8, 2) / 10.0;
	int x = mBottomRight.getX() - mTopLeft.getX();
	int y = mBottomRight.getY() - mPeople.getHeight();

	// X is random, Y must at the end of the last square
	x *= randomPercent;
	mPeople.setXY(x, y);
	mPeople.setLimitZone(mTopLeft, mBottomRight);
}

void CGAME::setAllVehicles() {
	m_pAllVehicles = NULL;
	int randomQtyTrucks = RandomInt(mNumberOfVehicles, 1);
	m_pTrucks = new CTRUCK[mNumberOfVehicles];
	int randomPosY = RandomInt(mNumberOfLane - 1, 0);
	int srcX = mTopLeft.getX();
	int desX = mBottomRight.getX();

	int y = mTopLeft.getY();

	for (int i = 0; i < mNumberOfVehicles; i++) {
		while (lanePosY[randomPosY] != 0) {
			randomPosY = RandomInt(mNumberOfLane - 1, 0);
		}
		m_pTrucks[i].setXY(0, 1);
		m_pTrucks[i].setStartPosX(-30);
		m_pTrucks[i].setLeft(srcX);
		m_pTrucks[i].setRight(desX);
	}
	m_pAllVehicles = { m_pTrucks };
}

void CGAME::setPlayingArea() {
	// Set the size of the playing area
	mPlayingAreaHeight = mWindowHeight * SCALE_X;
	mPlayingAreaWdth = mWindowWidth * SCALE_Y;

	// Set the top left point of the playing area
	mTopLeft = CPOINT2D(TOP_LEFT_X, TOP_LEFT_Y);
	mBottomRight = CPOINT2D(TOP_LEFT_X + mPlayingAreaWdth, TOP_LEFT_Y + mPlayingAreaHeight);
}

CGAME::CGAME() {
	// Get the console size
	mWindowHeight = GetHeightConsoleWindowBuffer();
	mWindowWidth = GetWidthConsoleWindowBuffer();

	mNumberOfLane = 7;
	lanePosY = vector<short>(mNumberOfLane, 0);
	isHasObject = vector<bool>(mNumberOfLane, false);

	mNumberOfVehicles = 1;

	// Set obj
	setPlayingArea();
	setAllVehicles();

	setPeople();
}

CGAME* CGAME::m_pGame = nullptr;

CGAME* CGAME::getGame() {
	if (m_pGame == nullptr)
		m_pGame = new CGAME();
	return m_pGame;
}

CGAME::~CGAME() {
	if (m_pTrucks != nullptr) {
		delete[] m_pTrucks;
		m_pTrucks = nullptr;
	}
}

CPEOPLE CGAME::getPeople() const {
	return mPeople;
}

CVEHICLE* CGAME::getVehicle() {
	if (m_pAllVehicles == nullptr)
		m_pAllVehicles = { m_pTrucks };
	return m_pAllVehicles;
}

CANIMAL* CGAME::getAnimal() {
	return nullptr;
}

void drawBorder(CPOINT2D topLeft, CPOINT2D bottomRight, COLOR color = COLOR::WHITE) {
	int index = 0;
	int height = bottomRight.getY() - topLeft.getY();
	int width = bottomRight.getX() - topLeft.getX();
	string outlineHorizontal = "";

	for (index = 1; index < width; ++index) {
		outlineHorizontal += HORIZONTAL_OUTLINE;
	}

	TextColor(color);

	// Draw the top outline
	GotoXY(topLeft.getX(), topLeft.getY());
	cout << TOP_LEFT_CORNER << outlineHorizontal << TOP_RIGHT_CORNER;

	// Draw the bottom outline
	GotoXY(topLeft.getX(), bottomRight.getY());
	cout << BOTTOM_LEFT_CORNER << outlineHorizontal << BOTTOM_RIGHT_CORNER;

	// Draw two vertical side of border
	for (index = 1; index < height; ++index) {
		GotoXY(topLeft.getX(), topLeft.getY() + index);
		cout << VERTICAL_OUTLINE;
		GotoXY(bottomRight.getX(), topLeft.getY() + index);
		cout << VERTICAL_OUTLINE;
	}
}

void CGAME::drawLane() const {
	// Draw lane base on number of lanes
	string lane = "";
	int gap = (mPlayingAreaHeight) * 1.0 / mNumberOfLane;
	int x = mTopLeft.getX() + 1;
	int y = mTopLeft.getY();

	// Get the lane string base on the width of playing area
	for (int index = 1; index < mPlayingAreaWdth; index++) {
		lane += LANE_ROAD;
	}

	TextColor(LANE_COLOR);
	// Draw the lane
	for (int pos = 1; pos <= mNumberOfLane; pos++) {
		y += gap;
		GotoXY(x, y);
		cout << lane;
	}
}

void CGAME::drawPlayingArea() const {
	// Draw the border line
	drawBorder(mTopLeft, mBottomRight, PLAYING_AREA_COLOR);
}

void  CGAME::drawVehicles() const {
	for (int index = 0; index < mNumberOfVehicles; index++) {
		m_pAllVehicles[index].drawVehicle();
	}
}

void  CGAME::drawAnimals() {
}

void CGAME::drawGame() const {
	// Erase the old obj on console screen
	drawPlayingArea();
	// Draw the road lane
	drawLane();

	// Draw people
	mPeople.drawPeople();
	drawVehicles();
}

void CGAME::resetGame() {
	if (m_pGame != nullptr) {
		delete m_pGame;
		m_pGame = new CGAME();
	}
}
void CGAME::exitGame(HANDLE handleThread) {
}

void CGAME::startGame() {
	resetGame();
}
void CGAME::loadGame(istream) {
}
void CGAME::saveGame(istream) {
}

void CGAME::pauseGame(HANDLE handleThread) const {
	SuspendThread(handleThread);
}

void CGAME::resumeGame(HANDLE handleThread) const {
	ResumeThread(handleThread);
}

void CGAME::updatePosPeople(DIRECTION direction) {
	if (mPeople.isHitLimit(direction) == true)
		return;

	if (direction == (DIRECTION)' ') {
		return;
	}
	mPeople.eraseTraceOfPeople();
	mPeople.Move(direction);
}

void CGAME::updatePosVehicle() {
	for (int index = 0; index < mNumberOfVehicles; index++) {
		m_pTrucks[index].updatePos(1);
	}
}

void CGAME::updatePosAnimal() {
}