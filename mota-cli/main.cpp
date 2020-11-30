#include <stdio.h>
using namespace std;

//for _kbhit function on Windows
#include <conio.h>
//for system function on Windows
#include <cstdlib>
//for string
#include <string> 
//for cin cout endl
#include<iostream>

//map struct
#define MAP_SIZE 11
#define MAP_FLOOR 0
#define MAP_WALL 1
#define MAP_WARRIOR 2

//door
#define DOOR_MIN 100
#define DOOR_YELLOW 101
#define DOOR_BLUE 102
#define DOOR_RED 103
#define DOOR_MAX 104

//item
#define ITEM_MIN 10000
//TODO items
#define ITEM_MAX 20000

//monster
#define MONSTER_MIN 20000
//TODO monsters
#define MONSTER_MAX 30000

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
	{0,101,0,1,0,102,0,1,0,103,0},
	{0,101,0,1,0,102,0,1,0,103,0},
	{0,101,0,1,0,102,0,1,0,103,0},
	{1,101,1,1,1,102,1,1,1,103,1},
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
int KeyRed = 3;

//key code on Windows
enum KeyCode
{
	Left_Arrow = 75,
	Up_Arrow = 72,
	Right_Arrow = 77,
	Down_Arrow = 80
};

//position
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
bool hitItem(int item);
int main()
{
	printMap();
	cout << endl;
	printWarriorStatus();

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
			cout << endl;
			printWarriorStatus();
		}
	}
}

void printMap()
{
	//上一个位置设置为地板
	//TODO 其他地形检测
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
	//位置
	cout << "位置:" << endl;
	cout << "x座标=" << positionX << ",y座标=" << positionY << endl;
	cout << endl;
	//钥匙
	cout << "钥匙:" << endl;
	cout << "黄钥匙=" << keyYellow << endl;
	cout << "蓝钥匙=" << keyBlue << endl;
	cout << "红钥匙=" << KeyRed << endl;
}

void movePosition(int position)
{
	//面向的物体
	int faceToItem = -1;
	switch (position)
	{
	case Position_Left:
		//左
		if (positionY > 0)
		{
			faceToItem = map[positionX][positionY - 1];
			if (faceToItem == MAP_FLOOR)
			{
				positionY -= 1;
			}
			else if(hitItem(faceToItem))
			{
				positionY -= 1;
			}
		}
		break;
	case Position_Up:
		//上
		if (positionX > 0)
		{
			faceToItem = map[positionX - 1][positionY];
			if (faceToItem == MAP_FLOOR)
			{
				positionX -= 1;
			}
			else if(hitItem(faceToItem))
			{
				positionX -= 1;
			}
		}
		break;
	case Position_Right:
		//右
		if (positionY < MAP_SIZE - 1)
		{
			faceToItem = map[positionX][positionY + 1];
			if (faceToItem == MAP_FLOOR)
			{
				positionY += 1;
			}
			else if(hitItem(faceToItem))
			{
				positionY += 1;
			}
		}
		break;
	case Position_Down:
		//下
		if (positionX < MAP_SIZE - 1)
		{
			faceToItem = map[positionX + 1][positionY];
			if (faceToItem == MAP_FLOOR)
			{
				positionX += 1;
			}
			else if(hitItem(faceToItem))
			{
				positionX += 1;
			}
		}
		break;
	default:
		break;
	}
}

bool hitItem(int item)
{
	//如果id范围为门
	if (item > DOOR_MIN && item < DOOR_MAX)
	{
		switch (item)
		{
		case DOOR_YELLOW:
			if (keyYellow >= 1)
			{
				keyYellow--;
				return true;
			}
			break;
		case DOOR_BLUE:
			if (keyBlue >= 1)
			{
				keyBlue--;
				return true;
			}
			break;
		case DOOR_RED:
			if (KeyRed >= 1)
			{
				KeyRed--;
				return true;
			}
			break;
		default:
			break;
		}
	}

	return false;
}