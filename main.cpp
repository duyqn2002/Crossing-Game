#include "CGAME.h"
#include "CCAR.h"

DIRECTION MOVING;
CGAME* game = CGAME::getGame();
int size = sizeof(game);

double FPS = (1.0/50) * 1000;
void renderGameThread() {
	while (true) {
		if (!game->getPeople().isDead()) {
			game->updatePosPeople(MOVING);
		}
		MOVING = (DIRECTION)' ';
		//game.updatePosVehicle();
		game->drawGame();
		Sleep(FPS);
	}
}

int main() {
	int temp;
	ResizeConsole(1024, 768); // width height
	FixConsoleWindow();
	ShowCursorConsole(false);
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

