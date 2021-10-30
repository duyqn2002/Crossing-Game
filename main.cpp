#include "CGAME.h"
#include "CCAR.h"

DIRECTION MOVING;
CGAME* game;
double FPS = 1000 / 60;


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
					GotoXY(x, y + i);
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

				string street = "                                            \n"
					"           | |               | |                        | |\n"
					"        ___| |_ _ __ ___  ___| |_    _ __ ___   __ _  __| |\n"
					"       / __| __| '__/ _ \\/ _ \\ __|  | '__/ _ \\ / _` |/ _` |\n"
					"       \\__ \\ |_| | |  __/  __/ |_   | | | (_) | (_| | (_| |\n"
					"       |___/\\__|_|  \\___|\\___|\\__|  |_|  \\___/ \\__,_|\\__,_|\n";
				GotoXY(17, 5);
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
	ConstructConsole(WINDOW_BUFFER_WIDTH, WINDOW_BUFFER_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
	//ResizeConsoleAndCenterConsole(WINDOW_BUFFER_WIDTH, WINDOW_BUFFER_HEIGHT);
	//menu();
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
	system("pause");
	return 0;
}