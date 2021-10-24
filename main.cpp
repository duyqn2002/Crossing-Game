#include "CGAME.h"
#include "CCAR.h"

DIRECTION MOVING;
CGAME* game;
int size = sizeof(game);

double FPS = (1.0/60) * 1000;
void renderGameThread() {
	while (true) {
		if (!game->getPeople().isDead()) {
			game->updatePosPeople(MOVING);
		}
		MOVING = (DIRECTION)' ';
		//game.updatePosVehicle();
		game->drawGame();
		deleteScreen();
		Sleep(FPS);
	}
}

int main() {
	int temp;
	
	ResizeConsole(980, 700); // width height 980 700
	FixConsoleWindow();
	ShowCursorConsole(false);
	game = CGAME::getGame();
	game->startGame();
	
	thread renderGame(renderGameThread);

	while (true) {
		temp = toupper(_getch());
	
	if (!game->getPeople().isDead()){
		if (temp == 27) {
				game->exitGame(renderGame.native_handle());
				return 0;
			}
			else if (temp == 'P') {
				game->pauseGame(renderGame.native_handle());
			}
			else {
				game->resumeGame(renderGame.native_handle());
				MOVING = (DIRECTION)temp; //Cập nhật bước di chuyển
			}
		}
	}

	//CVEHICLE* temp = new CTRUCK[2];
	//for (int i = 0; i < 2; ++i) {
	//	cout << temp->getName();
	//}
	
	//system("pause");
	return 0;
}

