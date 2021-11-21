#include "CGAME.h"

CGAME::CGAME()  {
	isPause = false;
	isPlaying = false;
	isPlayed = false;
	m_pConsole = Console::getConsole(WINDOW_BUFFER_WIDTH, WINDOW_BUFFER_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
	
	// Set obj
	setMainMenu();
	setSettingMenu();
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

	for (const auto& LaneInfo : mLanes) {
		int randomQty = RandomInt(3, 2);
		CLANE mLane(left, right);
		mLane.setY(y);
		mLane.setSpeed(LaneInfo.first);
		mLane.generateObjectsOnLane(LaneInfo.second, randomQty);
		switch (LaneInfo.second)		
		{
		case ENEMY::CCAR:
		case ENEMY::CTRUCK:
			mLane.enableTrafficLight();
		default:
			break;
		}

		if(mLane.size() != 0)
			mLaneOfEnemies.push_back(mLane);
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

CLANE CGAME::getEnemyLane()
{
	for (const auto& Lane : mLaneOfEnemies) {
		if (Lane.getY() == mPeople.getY())
			return Lane;
	}
	return CLANE();
}

void CGAME::drawPlayingArea() {
	// Draw the border line
	m_pConsole->DrawBorder(mTopLeft, mBottomRight, PLAYING_AREA_COLOUR);
}

void  CGAME::drawEnemies() {
	for (auto& Lane : mLaneOfEnemies) {
		Lane.drawObjectsOnLane(*m_pConsole);
	}
}

void CGAME::drawGame() {
	// Draw border
	drawPlayingArea();

	// Draw people
	mPeople.drawPeople(*m_pConsole);

	// Draw object
	drawEnemies();
}

void CGAME::renderGameThread(KEY* MOVING) {
	while (isPlaying) {
		if (isPause)
			continue;
		// Clear the old screen
		m_pConsole->ClearScreen();

		if (!mPeople.isDead()) {
			updatePosPeople(*MOVING);
		}
		*MOVING = KEY::SPACE;

		updatePosEnemies();

		drawGame();

		if (mPeople.isImpact(getEnemyLane())) {
			break;
			/*mPeople.animationWhenDead(*m_pConsole);
			mPeople.Dead();*/
		}

		if (mPeople.isFinish()) {
			nextLevel();
		}

		// Render out console
		m_pConsole->Render();
		Sleep(30);
	}
}

void CGAME::resetGame() {
	mLaneOfEnemies.clear();

	setObjects();
	setPeople();
}

void CGAME::playGame() {
	isPlaying = true;
	isPause = false;
	isPlayed = true;

	KEY MOVING = KEY::SPACE;
	KEY temp;

	mRenderGame = thread(&CGAME::renderGameThread, this, &MOVING);

	while (isPlaying) {
		temp = (KEY)toupper(_getch());
		if (!getPeople().isDead()) {
			if (temp == KEY::ESC) {
				exitGame();
				return;
			}
			else if (temp == KEY::PAUSE_GAME) {
				pauseGame();
			}
			else {
				resumeGame();
				MOVING = (KEY)temp;
			}
		}
		else {
			if (temp == KEY::YES) {
				resetGame();
			}
			else {
				exitGame();
				return;
			}
		}
	}
}

void CGAME::StartGame() {
	if (isPlayed) {
		int result = MessageBox(
			NULL,
			L"You will lost all the unsaved process.\nContine to create new game???", // Text in msg box
			L"New Game", // Msg box title
			MB_YESNO | MB_ICONWARNING | MB_TOPMOST | MB_APPLMODAL // Mode ask yes no
		);

		if (result == IDYES) {
			resetGame();
			playGame();
		}
	}else {
		if (mMainMenu.isHasOption("Continue") == false)
			mMainMenu.insertOption(1, "Continue", bind(&CGAME::playGame, this));
		playGame();
	}
}

void CGAME::setSettingMenu() {
	Texture gameTitle = \
		" ######  ######## ######## ######## #### ##    ##  ######\n"
		"##    ## ##          ##       ##     ##  ###   ## ##    ##\n"
		"##       ##          ##       ##     ##  ####  ## ##\n"
		" ######  ######      ##       ##     ##  ## ## ## ##   ####\n"
		"      ## ##          ##       ##     ##  ##  #### ##    ##\n"
		"##    ## ##          ##       ##     ##  ##   ### ##    ##\n"
		" ######  ########    ##       ##    #### ##    ##  ######";

	mSettingMenu.setMenuTitle(gameTitle,COLOUR::PINK);
	mSettingMenu.setMarginTop(4);
	mSettingMenu.addOption("Audio");
	mSettingMenu.addOption("Custom color");
	mSettingMenu.addOption("Back to main menu", bind(&CCenterMenu::QuitMenu, &mSettingMenu));
}

void CGAME::setMainMenu() {
	/*Texture gameTitle = "                                                     \n"
		"     | |               | |                        | |\n"
		"  __| | _ _ __  __| |    _ _ __   __ _  __| |\n"
		" / __| __| '__/ _ \\/ _ \\ __|  | '__/ _ \\ / _ |/ _ |\n"
		" \\__ \\ |_| | |  _/  __/ |   | | | (_) | (_| | (_| |\n"
		" |___/\\__|_|  \\___|\\___|\\__|  |_|  \\___/ \\__,_|\\__,_|\n";*/


	Texture gameTitle = \
		" ######  ########   #######   ######   ######  #### ##    ##  ######      ######      ###    ##     ## ########\n"
		"##    ## ##     ## ##     ## ##    ## ##    ##  ##  ###   ## ##    ##    ##    ##    ## ##   ###   ### ##       \n"
		"##       ##     ## ##     ## ##       ##        ##  ####  ## ##          ##         ##   ##  #### #### ##       \n"
		"##       ########  ##     ##  ######   ######   ##  ## ## ## ##   ####   ##   #### ##     ## ## ### ## ######   \n"
		"##       ##   ##   ##     ##       ##       ##  ##  ##  #### ##    ##    ##    ##  ######### ##     ## ##       \n"
		"##    ## ##    ##  ##     ## ##    ## ##    ##  ##  ##   ### ##    ##    ##    ##  ##     ## ##     ## ##       \n"
		" ######  ##     ##  #######   ######   ######  #### ##    ##  ######      ######   ##     ## ##     ## ######## \n";

	mMainMenu.setMenuTitle(gameTitle);
	mMainMenu.setMarginTop(4);
	mMainMenu.addOption("New Game", bind(&CGAME::StartGame, this));
	mMainMenu.addOption("Load Game", bind(&CGAME::loadGame, this));
	mMainMenu.addOption("Setting", bind(&CCenterMenu::Run, &mSettingMenu, ref(*m_pConsole)));
	mMainMenu.addOption("Quit", bind(&CCenterMenu::QuitMenu, &mMainMenu));
}

void CGAME::loadGame() {}

void CGAME::saveGame() {}

void CGAME::pauseGame() {
	isPause = true;
}

void CGAME::resumeGame() {
	isPause = false;
}

void CGAME::exitGame() {
	if (isPlaying) {
		isPlaying = false;
		mRenderGame.join();
	}
}

void CGAME::updatePosPeople(KEY direction) {
	mPeople.Move(direction,LANE_SIZE);
}

void CGAME::updatePosEnemies() {
	for (auto& Lane : mLaneOfEnemies) {
		Lane.updateObjectsOnLane();
	}
}

void CGAME::Run() {
	mMainMenu.Run(*m_pConsole);
}
