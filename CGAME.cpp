#include "CGAME.h"

CGAME* CGAME::m_pGame = nullptr;

CGAME* CGAME::getGame() {
	if (m_pGame == nullptr)
		m_pGame = new CGAME();
	return m_pGame;
}

void CGAME::setPeople() {
	// Set the position of people
	// Generate randomly X by multiplying a floating number between 0.2 to 0.8
	float randomPercent = (float) RandomInt(8, 2) / 10.0f;
	int x = mBottomRight.getX() - mTopLeft.getX();
	int y = mBottomRight.getY() - mPeople.getHeight();

	// X is random, Y must at the end of the last square
	x = x * randomPercent;
	mPeople.setXY(x, y);
	mPeople.setLimitZone(mTopLeft, mBottomRight);
}

void CGAME::setPlayingArea() {
	// Set the size of the playing area
	int mPlayingAreaHeight = WINDOW_BUFFER_HEIGHT * SCALE_Y - 1;
	int mPlayingAreaWdth = WINDOW_BUFFER_WIDTH * SCALE_X - 1;

	// Set the top left point of the playing area
	mTopLeft = CPOINT2D(TOP_LEFT_X, TOP_LEFT_Y);
	mBottomRight = CPOINT2D(TOP_LEFT_X + mPlayingAreaWdth, TOP_LEFT_Y + mPlayingAreaHeight);
}

CGAME::CGAME() {
	// Set obj
	setPlayingArea();
	setPeople();
}

CPEOPLE CGAME::getPeople() const {
	return mPeople;
}

vector<CVEHICLE> CGAME::getVehicles() const{
	vector<CVEHICLE> allVehicles;
	allVehicles.insert(allVehicles.end(), m_vecTrucks.begin(),m_vecTrucks.end());
	allVehicles.insert(allVehicles.end(), m_vecCars.begin(), m_vecCars.end());

	return allVehicles;
}

vector<CANIMAL> CGAME::getAnimals() const{
	vector<CANIMAL> allAnimals;

	return allAnimals;
}

void drawBorder(CPOINT2D topLeft, CPOINT2D bottomRight, COLOUR color = COLOUR::WHITE) {
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

void CGAME::drawPeopleSafeLane(int x1,int y1,int x2,int y2) const{
	/*GotoXY(x1, y1);
	int index = 0;
	int white = 119;
	int gray = 136;
	string lane = "";

	TextColor((COLOUR)white);
	for (index = x1; index < x2 - 1; ++index) {
		lane += " ";
	}
	cout << lane;

	TextColor((COLOUR)gray);
	for (index = y1 + 1; index < y2 - 1; ++index) {
		GotoXY(x1,  index);
		cout << lane;
	}

	TextColor((COLOUR)255);
	GotoXY(x1,index);
	cout << lane;*/
}

void CGAME::drawPlayingArea() const {
	// Draw the border line
	drawBorder(mTopLeft, mBottomRight, PLAYING_AREA_COLOUR);
}

void  CGAME::drawVehicles() const {
}

void  CGAME::drawAnimals() {
}

void CGAME::drawGame() const {
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

void CGAME::updatePosPeople(DIRECTION direction) {
	if (mPeople.isHitLimit(direction) == true)
		return;
	if (direction == (DIRECTION)' ') {
		return;
	}
	mPeople.eraseTraceOfPeople();
	mPeople.Move(direction,LANE_SIZE);
}

void CGAME::updatePosVehicle() {

}

void CGAME::updatePosAnimal() {
}