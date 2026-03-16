#pragma once
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 40
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define WIN_SCORE 50
#define SCORE_FILE "scores.dat"
#define MAX_RECORDS 100

typedef enum
{
	FOOD_NORMAL = 0,
	FOOD_BIG = 1,
	FOOD_SMALL = 2
} FoodType;

typedef struct
{
	int x;
	int y;
}Snakenode;

typedef struct
{
	int x;
	int y;
	FoodType type;
}Food;

typedef struct
{
	Snakenode snakeNode[1000];
	int length;
	int speed;
}Snake;

typedef struct
{
	char name[20];
	int score;
	char date[20];
}ScoreRecord;

void GotoXY(int, int);
void Hide();
int Menu();
void Help();
void About();
void InitMap();
void PrintFood();
int MoveSnake();
int IsCorrect();
void SpeedControl();
void ShowWinScreen(int);
void SaveScore(int);
void ShowLeaderboard();
void LoadScores(ScoreRecord[], int*);
void SortScores(ScoreRecord[], int);