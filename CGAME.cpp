#include "CGAME.h"

void CGAME::setRandomPostionTrucks(const int& numberOfTrucks) {
	
}

void CGAME::setPeople() {
	// Set the position of people
	// Generate randomly X by multipling a floating number between 0.2 to 0.8
	float randomPercent =  RandomInt(8,2) / 10.0;
	int x = this->mBottomRight.getX() - this->mTopLeft.getX();
	int y = this->mBottomRight.getY() - this->mPeople.getHeight();

	// X is random, Y must at the end of the last square
	x *= randomPercent;	
	this->mPeople.setXY(x, y);
	this->mPeople.setLimitZone(this->mTopLeft, this->mBottomRight);
}

void CGAME::setAllVehicles() {
	this->m_pAllVehicals = new CVEHICLE[this->mNumberOfVehicles];
	this->setRandomPostionTrucks(this->mNumberOfVehicles);
}

void CGAME::setPlayingArea() {
	// Set the size of the playing area
	this->mPlayingAreaHeight = this->mWindowHeight * SCALE_X;
    this->mPlayingAreaWdth = this->mWindowWidth * SCALE_Y;

	// Set the top left point of the playing area
	this->mTopLeft = CPOINT2D(TOP_LEFT_X, TOP_LEFT_Y);
	this->mBottomRight = CPOINT2D(TOP_LEFT_X + this->mPlayingAreaWdth, TOP_LEFT_Y + this->mPlayingAreaHeight);
}

CGAME::CGAME() {
	// Get the console size
	this->mWindowHeight = GetHeightConsoleWindowBuffer();
	this->mWindowWidth = GetWidthConsoleWindowBuffer();

	// Set obj
	this->setPlayingArea();
	this->setPeople();

	this->mNumberOfLane = 5;
	this->isHasObject = vector<bool>( this->mNumberOfLane, false);

	this->mNumberOfVehicles = 2;	
	this->setAllVehicles();
}

CGAME* CGAME::mGame = NULL;

CGAME* CGAME::getGame() {
	if (mGame == NULL)
		mGame = new CGAME();
	return mGame;
}

CGAME::~CGAME() {
	if (this != NULL) {
		if (this->m_pTrucks != NULL) {
			delete[] m_pTrucks;
			this->m_pTrucks = NULL;
		}
	}
}

CPEOPLE CGAME::getPeople() {
	return this->mPeople;
}

CVEHICLE* CGAME::getVehicle() {
	return this->m_pAllVehicals;
}

CANIMAL* CGAME::getAnimal() {
	return NULL;
}

void drawBorder(CPOINT2D topLeft, CPOINT2D bottomRight,COLOR color = COLOR::WHITE) {
	int index = 0;
	int height = bottomRight.getY() - topLeft.getY();
	int width = bottomRight.getX() - topLeft.getX();
	string outlineHorizontal = "";

	for (index = 1; index < width; ++index) {
		outlineHorizontal += HORIZONTAL_OUTLINE;
	}
	TextColor(color);

	GotoXY(topLeft.getX(), topLeft.getY());
	cout << TOP_LEFT_CORNER << outlineHorizontal << TOP_RIGHT_CORNER;

	GotoXY(topLeft.getX(), bottomRight.getY());
	cout << BOTTOM_LEFT_CORNER << outlineHorizontal << BOTTOM_RIGHT_CORNER;

	for (index = 1; index < height; ++index) {
		GotoXY(topLeft.getX(), topLeft.getY() + index);
		cout << VERTICAL_OUTLINE;
		GotoXY(bottomRight.getX(),topLeft.getY() + index);
		cout << VERTICAL_OUTLINE;
	}
}

void CGAME::drawLane() {
	// Draw lane base on number of lanes
	char laneChar = 196;
	string lane = "";
	int gap = (this->mPlayingAreaHeight - this->mPeople.getHeight()) * 1.0 / this->mNumberOfLane; // do dai - chieu cao nhan vat / so lane
	int x = this->mTopLeft.getX() + 1;
	int y = this->mTopLeft.getY();

	for (int index = 1; index < this->mPlayingAreaWdth; index++) {
		lane += laneChar;
	}
	
	TextColor(LANE_COLOR);
	for (int pos = 1; pos <= this->mNumberOfLane; pos++) {
		y += gap;
		GotoXY(x, y);
		cout << lane;
	}
}

void CGAME::drawPlayingArea() {
	// Draw the border line
	drawBorder(this->mTopLeft,this->mBottomRight,PLAYING_AREA_COLOR);
}

void  CGAME::drawVehicles() {
	for (int index = 0; index < this->mNumberOfVehicles; index++) {
		this->m_pTrucks[index].drawVehicle();
	}
}

void  CGAME::drawAnimals() {

}

void CGAME::drawGame() {
	// Erase the old obj on console screen
	//this->mPlayer.eraseTraceOfPeople();
	this->drawPlayingArea();
	// Draw the road lane
	this->drawLane();

	// Draw people
	this->mPeople.drawPeople();
	//this->drawVehicles();
}

void CGAME::resetGame() {
	if (this != NULL) {
	
	}
}
void CGAME::exitGame(HANDLE handleThread) {
	
}

void CGAME::startGame() {
	this->resetGame();
	// Draw the playing area with the Lane
	drawPlayingArea();
	this->drawGame();
}
void CGAME::loadGame(istream) {

}
void CGAME::saveGame(istream) {

}

void CGAME::pauseGame(HANDLE handleThread) {
	SuspendThread(handleThread);
}

void CGAME::resumeGame(HANDLE handleThread) {
	ResumeThread(handleThread);
}

void CGAME::updatePosPeople(DIRECTION direction) {
	if (this->mPeople.isHitLimit(direction) == true)
		return;

	if (direction == (DIRECTION)' ') {
		return;
	}
	this->mPeople.Move(direction);
}

void CGAME::updatePosVehicle() {
	for (int index = 0; index < this->mNumberOfVehicles; index++) {
		this->m_pTrucks[index].erase();
		this->m_pTrucks[index].updatePos(1);
	}
}

void CGAME::updatePosAnimal() {
}