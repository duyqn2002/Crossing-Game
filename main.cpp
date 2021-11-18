#include "CGAME.h"

int main() {
	CGAME* game = CGAME::getGame();
	game->startGame();
	return 0;
}
