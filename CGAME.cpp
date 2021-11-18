#include "CGAME.h"

CGAME::CGAME()  {
	isPlaying = false;
	m_pConsole = Console::getConsole(WINDOW_BUFFER_WIDTH, WINDOW_BUFFER_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
	// Set obj
	setPlayingArea(SCALE_X, SCALE_Y);
	setObjects();
	setPeople();
}

CGAME* CGAME::getGame() {
	static CGAME mInstance;
	return &mInstance;
}

CGAME::~CGAME() {}

void CGAME::setObjects() {
	int left = mTopLeft.getX();
	int right = mBottomRight.getX();

	int y = mTopLeft.getY() + 1;

	for (const auto& lane : mLanes) {
		int randomQty = RandomInt(3, 2);
		CLANE<CANIMAL> tempAnimals(left, right);
		CLANE<CVEHICLE> tempVehicles(left, right);

		switch (lane.second)
		{
		
		case ENEMY::CTRUCK:
		case ENEMY::CCAR:
			tempVehicles.setY(y);
			tempVehicles.setSpeed(lane.first);
			tempVehicles.generateObjectsOnLane(lane.second, randomQty);
			tempVehicles.enableTrafficLight();
			mVehiclesLane.push_back(tempVehicles);
			break;

		case ENEMY::CDOG:
		case ENEMY::CBIRD:
			tempAnimals.setY(y);
			tempAnimals.setSpeed(lane.first);
			tempAnimals.generateObjectsOnLane(lane.second, randomQty);
			mAnimalsLane.push_back(tempAnimals);
			break;

		default:
			break;
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
	int mPlayingAreaHeight = m_pConsole->Height() * scaleY - 1;
	int mPlayingAreaWdth = m_pConsole->Width() * scaleX - 1;

	// Set the top left point of the playing area
	mTopLeft = CPOINT2D(TOP_LEFT_X, TOP_LEFT_Y);
	mBottomRight = CPOINT2D(TOP_LEFT_X + mPlayingAreaWdth, TOP_LEFT_Y + mPlayingAreaHeight);
}

CPEOPLE CGAME::getPeople() const {
	return mPeople;
}

CLANE<CVEHICLE> CGAME::getVehicles() const{
	for (const auto& Lane : mVehiclesLane) {
		if (mPeople.getY() == Lane.getY())
			return Lane;
	}

	return CLANE<CVEHICLE>();
}

CLANE<CANIMAL> CGAME::getAnimals() const{
	for (const auto& Lane : mAnimalsLane) {
		if (mPeople.getY() == Lane.getY())
			return Lane;
	}

	return CLANE<CANIMAL>();
}

void CGAME::drawPlayingArea() {
	// Draw the border line
	m_pConsole->DrawBorder(mTopLeft, mBottomRight, PLAYING_AREA_COLOUR);
}

void  CGAME::drawVehicles() {
	for (auto& Lane : mVehiclesLane) {
		Lane.drawObjectsOnLane(*m_pConsole);
	}
}

void  CGAME::drawAnimals() {
	for (auto& Lane : mAnimalsLane) {
		Lane.drawObjectsOnLane(*m_pConsole);
	}
}

void CGAME::drawGame() {
	// Clear the old screen
	m_pConsole->ClearScreen();

	// Draw border
	drawPlayingArea();

	// Draw people
	mPeople.drawPeople(*m_pConsole);

	//// Draw object
	drawVehicles();
	drawAnimals();

	// Render out console
	m_pConsole->Render();
}

void CGAME::resetGame() {
	mVehiclesLane.clear();
	mAnimalsLane.clear();

	setObjects();
	setPeople();
}

int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return -1;
	}

	return -1;
}

void menu() {
	const string choice[4] = { "New Game","Load Game","Settings","Quit" };
	int pos = 0;
	int x = 35, y = 15;
	//if (!SetOption::mute)PlaySound(TEXT("PUBG.wav"), NULL, SND_ASYNC);
	bool changeInput = true;
	while (true) {
		changeInput = true;

		//if (!SetOption::mute)PlaySound(TEXT("PUBG.wav"), NULL, SND_ASYNC);
		while (true) {
			if (changeInput) {
				system("cls");
				//map.printBorder();
				for (int i = 0; i < 4; i++) {
					//GotoXY(x, y + i);
					if (i == pos)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					cout << choice[i] << endl;
				}

				//TextColor(7);

				string street = "                                                     \n"
					"     | |               | |                        | |\n"
					"  __| | _ _ __  __| |    _ _ __   __ _  __| |\n"
					" / __| __| '__/ _ \\/ _ \\ __|  | '__/ _ \\ / _ |/ _ |\n"
					" \\__ \\ |_| | |  _/  __/ |   | | | (_) | (_| | (_| |\n"
					" |___/\\__|_|  \\___|\\___|\\__|  |_|  \\___/ \\__,_|\\__,_|\n";
				//GotoXY(17, 5);
				cout << street;
			}
			//cout << street;
			changeInput = false;
			switch (inputKey()) {
				changeInput = true;
				//PlaySound(TEXT("RING.wav"), NULL, SND_ASYNC);
			case 'w':
				changeInput = true;
				pos--;
				pos = (pos + 4) % 4;
				break;
			case 's':
				changeInput = true;
				pos++;
				pos %= 4;
				break;
			case 13:
				switch (pos) {
				case 0:
				{

					cout << "them vao dayu";
					break;

				}
				case 1: {
					cout << "hello";
					break;

				}
				case 2:
				{
					cout << "setting";
					break;
				}
				case 3:
				{
					system("cls");
					cout << "quit";
				}
				}


			}
		}
	}
}

void CGAME::renderGameThread(KEY* MOVING) {
	while (isPlaying) {
		if (isPause == true)
			continue;

		if (!getPeople().isDead()) {
			updatePosPeople(*MOVING);
		}
		*MOVING = KEY::STAND_STILL;

		updatePosVehicle();
		updatePosAnimal();

		drawGame();

		if (getPeople().isImpact(getVehicles()) || getPeople().isImpact(getAnimals())) {
			break;
		}

		if (getPeople().isFinish()) {
			nextLevel();
		}

		Sleep(30);
	}
}

void CGAME::startGame() {
	KEY MOVING = KEY::STAND_STILL;
	KEY temp;

	isPlaying = true;
	mRenderGame = thread(&CGAME::renderGameThread, this, &MOVING);

	while (true) {
		temp = (KEY)toupper(_getch());
		if (!getPeople().isDead()) {
			if (temp == KEY::ESC) {
				exitGame();
				return;
			}
			else if (temp == KEY::PAUSE) {
				pauseGame();
			}
			else {
				resumeGame();
				MOVING = (KEY)temp;
			}
		}
		
	}
}

void CGAME::loadGame(istream) {}

void CGAME::saveGame(istream) {}

void CGAME::pauseGame() {
	isPause = true;
}

void CGAME::resumeGame() {
	isPause = false;
}

void CGAME::exitGame() {
	isPlaying = false;
	mRenderGame.join();
}

void CGAME::updatePosPeople(KEY direction) {
	mPeople.Move(direction,LANE_SIZE);
}

void CGAME::updatePosVehicle() {
	for (auto& Lane : mVehiclesLane) {
		Lane.updateObjectsOnLane();
	}
}

void CGAME::updatePosAnimal() {
	for (auto& Lane : mAnimalsLane) {
		Lane.updateObjectsOnLane();
	}
}
