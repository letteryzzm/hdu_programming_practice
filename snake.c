#include "snake.h"
Snake snake;
Food food;
char now_Dir = RIGHT;
char direction = RIGHT;
int currentScore = 0;

int Menu()
{
	GotoXY(40, 12);
	printf("��ӭ����̰����С��Ϸ");
	GotoXY(43, 14);
	printf("1.��ʼ��Ϸ");
	GotoXY(43, 16);
	printf("2.����");
	GotoXY(43, 18);
	printf("3.����");
	GotoXY(43, 20);
	printf("4.�����а�");
	GotoXY(43, 22);
	printf("����������˳���Ϸ");
	Hide();
	char ch;
	int result = 0;
	ch = _getch();
	switch (ch) {
	case '1': result = 1; break;
	case '2': result = 2; break;
	case '3': result = 3; break;
	case '4': result = 4; break;
	}
	system("cls");
	return result;
}

void GotoXY(int x, int y) {
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}

void Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
	SetConsoleCursorInfo(hout, &cor_info);
}

void About()
{
	GotoXY(30, 12);
	printf("���ݵ��ӿƼ���ѧ������������ۺ�ʵ������");
	GotoXY(43, 14);
	printf("̰����-����̨��Ϸ");
	GotoXY(43, 16);
	printf("������������ϼ��˵�");
	Hide();
	char ch = _getch();
	system("cls");
}

void Help()
{
	GotoXY(40, 12);
	printf("w ��");
	GotoXY(40, 14);
	printf("s ��");
	GotoXY(40, 16);
	printf("a ��");
	GotoXY(40, 18);
	printf("d ��");
	GotoXY(40, 20);
	printf("����ײ��������ײǽʱ��Ϸ����");
	GotoXY(45, 22);
	printf("������������ϼ��˵�");
	Hide();
	char ch = _getch();
	system("cls");
}

void InitMap()
{
	Hide();
	snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
	snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	printf("@");
	snake.length = 3;
	snake.speed = 250;
	now_Dir = RIGHT;
	currentScore = 0;
	for (int i = 1; i < snake.length; i++) {
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
		printf("o");
	}

	for (int i = 0; i < MAP_WIDTH; i++) {
		GotoXY(i, 0);
		printf("-");
		GotoXY(i, MAP_HEIGHT - 1);
		printf("-");
	}

	for (int i = 1; i < MAP_HEIGHT - 1; i++) {
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_WIDTH - 1, i);
		printf("|");
	}

	PrintFood();

	GotoXY(50, 5);
	printf("��ǰ�÷�:0");
}

void PrintFood()
{
	int flag = 1;
	int randType;
	while (flag) {
		flag = 0;
		food.x = rand() % (MAP_WIDTH - 2) + 1;
		food.y = rand() % (MAP_HEIGHT - 2) + 1;
		for (int k = 0; k <= snake.length - 1; k++) {
			if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
				flag = 1;
				break;
			}
		}
	}

	randType = rand() % 100;
	if (randType < 70) {
		food.type = FOOD_NORMAL;
	} else if (randType < 90) {
		food.type = FOOD_BIG;
	} else {
		food.type = FOOD_SMALL;
	}

	GotoXY(food.x, food.y);
	if (food.type == FOOD_NORMAL) {
		printf("$");
	} else if (food.type == FOOD_BIG) {
		printf("#");
	} else {
		printf("*");
	}
}

int MoveSnake()
{
	Snakenode temp;
	int flag = 0;
	temp = snake.snakeNode[snake.length - 1];
	for (int i = snake.length - 1; i >= 1; i--) {
		snake.snakeNode[i] = snake.snakeNode[i - 1];
	}
	GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
	printf("o");

	if (_kbhit()) {
		direction = _getch();
		switch (direction) {
		case UP:
			if (now_Dir != DOWN)
				now_Dir = direction;
			break;
		case DOWN:
			if (now_Dir != UP)
				now_Dir = direction;
			break;
		case LEFT:
			if (now_Dir != RIGHT)
				now_Dir = direction;
			break;
		case RIGHT:
			if (now_Dir != LEFT)
				now_Dir = direction;
			break;
		}
	}
	switch (now_Dir) {
	case UP:snake.snakeNode[0].y--; break;
	case DOWN:snake.snakeNode[0].y++; break;
	case LEFT:snake.snakeNode[0].x--; break;
	case RIGHT:snake.snakeNode[0].x++; break;
	}

	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	printf("@");

	if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
		flag = 1;
		if (food.type == FOOD_NORMAL) {
			snake.length++;
			snake.snakeNode[snake.length - 1] = temp;
			currentScore++;
		} else if (food.type == FOOD_BIG) {
			snake.length += 2;
			snake.snakeNode[snake.length - 2] = temp;
			snake.snakeNode[snake.length - 1] = temp;
			currentScore += 3;
		} else {
			currentScore += 5;
		}
	}

	if (!flag) {
		GotoXY(temp.x, temp.y);
		printf(" ");
	}
	else {
		PrintFood();
		GotoXY(50, 5);
		printf("��ǰ�÷�: %d", currentScore);
	}

	if (currentScore >= WIN_SCORE) {
		ShowWinScreen(currentScore);
		return 0;
	}

	if (!IsCorrect()) {
		system("cls");
		GotoXY(45, 14);
		printf("���յ÷�: %d", currentScore);
		GotoXY(45, 16);
		printf("�����ˣ�");
		SaveScore(currentScore);
		GotoXY(45, 18);
		printf("��������������˵�");
		char c = _getch();
		system("cls");
		return 0;
	}

	SpeedControl();
	Sleep(snake.speed);
	return 1;
}

int IsCorrect() {
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 || snake.snakeNode[0].y == MAP_HEIGHT - 1)
	return 0;
	for (int i = 1; i < snake.length; i++) {
		if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y)
			return 0;
	}
	return 1;
}

void SpeedControl() {
	switch (snake.length) {
	case 6:snake.speed = 200; break;
	case 9:snake.speed = 180; break;
	case 12:snake.speed = 160; break;
	case 15:snake.speed = 140; break;
	case 18:snake.speed = 120; break;
	case 21:snake.speed = 100; break;
	case 24:snake.speed = 80; break;
	case 27:snake.speed = 60; break;
	case 30:snake.speed = 40; break;
	default:break;
	}
}

void ShowWinScreen(int score)
{
	system("cls");
	GotoXY(45, 12);
	printf("��ϲ��ʤ��");
	GotoXY(45, 14);
	printf("���յ÷�: %d", score);
	GotoXY(45, 16);
	printf("�Ѵﵽ��ʤ�÷�: %d", WIN_SCORE);
	SaveScore(score);
	GotoXY(45, 18);
	printf("��������������˵�");
	Hide();
	char c = _getch();
	system("cls");
}
void SaveScore(int score)
{
	ScoreRecord record;
	FILE* file;
	time_t now;
	struct tm* timeinfo;
	
	printf("\n");
	GotoXY(40, 20);
	printf("������������: ");
	scanf("%s", record.name);
	
	record.score = score;
	time(&now);
	timeinfo = localtime(&now);
	sprintf(record.date, "%04d-%02d-%02d", 
		timeinfo->tm_year + 1900, 
		timeinfo->tm_mon + 1, 
		timeinfo->tm_mday);
	
	file = fopen(SCORE_FILE, "ab");
	if (file != NULL) {
		fwrite(&record, sizeof(ScoreRecord), 1, file);
		fclose(file);
	}
}

void LoadScores(ScoreRecord records[], int* count)
{
	FILE* file;
	*count = 0;
	
	file = fopen(SCORE_FILE, "rb");
	if (file != NULL) {
		while (fread(&records[*count], sizeof(ScoreRecord), 1, file) == 1) {
			(*count)++;
			if (*count >= MAX_RECORDS) break;
		}
		fclose(file);
	}
}

void SortScores(ScoreRecord records[], int count)
{
	int i, j;
	ScoreRecord temp;
	
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - i - 1; j++) {
			if (records[j].score < records[j + 1].score) {
				temp = records[j];
				records[j] = records[j + 1];
				records[j + 1] = temp;
			}
		}
	}
}

void ShowLeaderboard()
{
	ScoreRecord records[MAX_RECORDS];
	int count, i, displayCount;
	
	LoadScores(records, &count);
	SortScores(records, count);
	
	system("cls");
	GotoXY(45, 8);
	printf("=== �����а� ===");
	GotoXY(35, 10);
	printf("����        ����        ����");
	
	displayCount = count > 10 ? 10 : count;
	for (i = 0; i < displayCount; i++) {
		GotoXY(35, 12 + i);
		printf("%-12s %-12d %s", records[i].name, records[i].score, records[i].date);
	}
	
	if (count == 0) {
		GotoXY(40, 12);
		printf("��û�м�¼");
	}
	
	GotoXY(45, 24);
	printf("��������������˵�");
	Hide();
	char c = _getch();
	system("cls");
}
