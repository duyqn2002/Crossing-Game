#include "CGAME.h"

int main() {
	CGAME* game = CGAME::getGame();
	game->Run();
	
	//PlaySound(TEXT("AlienShip.wav"), NULL, SND_FILENAME | SND_SYNC);
	return 0;
}
