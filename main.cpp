#include "CGAME.h"
#include "CCAR.h"

DIRECTION MOVING;
CGAME* game;
double FPS = 1000 / 60;

void renderGameThread() {
	while (true) {
		if (!game->getPeople().isDead()) {
			game->updatePosPeople(MOVING);
		}
		MOVING = (DIRECTION)' ';
		game->updatePosVehicle();
		game->drawGame();
		Sleep(FPS);
	}
}

int main() {
	int temp;
	ResizeConsoleAndCenterConsole(WINDOW_HEIGHT, WINDOW_WIDTH);
	FixConsoleWindow();
	ShowCursorConsole(false);
	game = CGAME::getGame();
	game->startGame();
	thread renderGame(renderGameThread);

	while (true) {
		temp = toupper(_getch());
		if (!game->getPeople().isDead()) {
			if (temp == 27) {
				game->exitGame(renderGame.native_handle());
				return 0;
			}
			else if (temp == 'P') {
				game->pauseGame(renderGame.native_handle());
			}
			else {
				game->resumeGame(renderGame.native_handle());
				MOVING = (DIRECTION)temp;
			}
		}
	}

	return 0;
}