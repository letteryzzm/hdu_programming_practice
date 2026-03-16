#include "snake.h"
int main()
{
	srand((unsigned int)time(0));
	int end = 1, result;
	while (end) {
		result = Menu();
		switch (result) {
		case 1:
			InitMap();
			while (MoveSnake());
			break;
		case 2:
			Help();
			break;
		case 3:
			About();
			break;
		case 4:
			ShowLeaderboard();
			break;
		case 0:
			end = 0;
			break;
		}
	}
}