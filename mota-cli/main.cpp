#include <stdio.h>
using namespace std;

//for _kbhit function on Windows
#include <conio.h>
//for system function on Windows
#include <cstdlib>
//for string
#include <string> 

//map struct
#define MAP_SIZE 11
#define MAP_FLOOR 0
#define MAP_WALL 1
#define MAP_WARRIOR 2
//door
#define DOOR_YELLOW 100
#define DOOR_BLUE 101
#define DOOR_RED 102

//char map[MAP_SIZE][MAP_SIZE] =
//{
//	{1,1,1,1,1,1,1,1,1,1,1},
//	{1,1,0,0,1,0,1,0,0,1,1},
//	{1,0,0,0,1,0,1,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,1},
//	{1,1,1,1,1,0,1,1,1,1,1},
//	{0,0,0,0,1,0,1,0,0,0,0},
//	{0,0,0,0,1,0,1,0,0,0,0},
//	{0,0,0,0,1,0,1,0,0,0,0},
//	{0,0,0,0,1,0,1,0,0,0,0}
//};

char map[MAP_SIZE][MAP_SIZE] =
{
	{0,0,0,1,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,1,0,0,0},
	{1,100,1,1,1,101,1,1,1,102,1},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0}
};

//warrior position
int positionX = 10;
int positionY = 5;
//warrior last position
int positionLastX = positionX;
int positionLastY = positionY;
//keys
int keyYellow = 3;
int keyBlue = 3;
int Keyred = 3;


enum KeyCode
{
	Left_Arrow = 75,
	Up_Arrow = 72,
	Right_Arrow = 77,
	Down_Arrow = 80
};

enum Position
{
	Position_Left,
	Position_Up,
	Position_Right,
	Position_Down
};

void printMap();
void printWarriorStatus();
void movePosition(int position);
int main()
{
	printMap();
	while (true)
	{
		string messageStatus = "";
		
		if (_kbhit())
		{
			int key = _getch();
			switch (key)
			{
			case Left_Arrow:
				//left
				movePosition(Position_Left);
				break;
			case Up_Arrow:
				//up
				movePosition(Position_Up);
				break;
			case Right_Arrow:
				//right
				movePosition(Position_Right);
				break;
			case Down_Arrow:
				//down
				movePosition(Position_Down);
				break;
			default:
				break;
			}

			system("cls");
			printMap();
		}
	}
}

void printMap()
{
	//上一个位置设置为地板
	map[positionLastX][positionLastY] = MAP_FLOOR;
	//移动到新的位置
	map[positionX][positionY] = MAP_WARRIOR;
	//更新上一个位置
	positionLastX = positionX;
	positionLastY = positionY;

	for (size_t x = 0; x < MAP_SIZE; x++)
	{
		printf("|");
		for (size_t y = 0; y < MAP_SIZE; y++)
		{
			int mapValue = map[x][y];
				switch (mapValue)
				{
				case MAP_FLOOR:
					printf("  ");
					break;
				case MAP_WALL:
					printf("墙");
					break;
				case MAP_WARRIOR:
					printf("人");
					break;
				case DOOR_YELLOW:
					printf("黄");
					break;
				case DOOR_BLUE:
					printf("蓝");
					break;
				case DOOR_RED:
					printf("红");
					break;
				default:
					break;
				}
			printf("|");
		}
		printf("\n");
	}
}

void printWarriorStatus()
{

}

void movePosition(int position)
{
	switch (position)
	{
	case Position_Left:
		//left
		if (positionY > 0)
		{
			if (map[positionX][positionY - 1] == MAP_FLOOR)
			{
				positionY -= 1;
			}
		}
		break;
	case Position_Up:
		//up
		if (positionX > 0)
		{
			if (map[positionX - 1][positionY] == MAP_FLOOR)
			{
				positionX -= 1;
			}
		}
		break;
	case Position_Right:
		//right
		if (positionY < MAP_SIZE - 1)
		{
			if (map[positionX][positionY + 1] == MAP_FLOOR)
			{
				positionY += 1;
			}
		}
		break;
	case Position_Down:
		//down
		if (positionX < MAP_SIZE - 1)
		{
			if (map[positionX + 1][positionY] == MAP_FLOOR)
			{
				positionX += 1;
			}
		}
		break;
	default:
		break;
	}
}