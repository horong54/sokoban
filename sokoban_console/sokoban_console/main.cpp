/***********************************
 Very simple sokoban implementation 
                         by Hobytes
   				            1993. 8
(2013.10: some bug fix)
************************************/
#include <conio.h>
#include <iostream>

#define KEY_ESC 27
#define KEY_ARROW 224
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_RESET 114

#define LEFT KEY_LEFT
#define RIGHT KEY_RIGHT
#define UP KEY_UP
#define DOWN KEY_DOWN

#define WALL 1
#define PLAYER 2
#define BALL 3
#define EXIT 4

#define MW 10

int getInput();
void updateGame(int direction);
void draw();

int map[MW][MW] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},					
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},					
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

//start data;
int px, py, bx, by, ex, ey, turn;

int main() {
	using namespace std; 	
	int key;			

reset:
	turn  = 0;
	px = 4, py = 4;
	bx = 5, by = 4;
	ex = 2, ey = 2;	

	cout << "Simple Push Push Game by Hobytes ver. 0.2" << endl;
	cout << "Press space bar to start..." << endl;	

	while ((key = getInput() ) != KEY_ESC ) {
		if (key == KEY_RESET) {
			map[py][px] = 0;
			map[by][bx] = 0;
			system("cls");
			goto reset;
		}
		turn++;
		updateGame(key);
		draw();

		if( bx == ex && by == ey) {
			cout << "\nYou're very smart! Clear!!" << endl;
			break;
		}
	}

	std::cout << "Thanks for playing!!" << endl;

	return 0;
}

int getInput() {
	int key = _getch();	
	std::cout << key << std::endl;
	if(key == KEY_ARROW )
		key = _getch();
	return key;
}

//check whether obj1 is in front of obj2
int is_front(int direction, int x1, int y1, int x2, int y2) {
	switch(direction) {
	case LEFT:
		if (y1 == y2 && (x1 + 1) == x2)
			return 1;
		break;
	case RIGHT:
		if (y1 == y2 && (x1 - 1) == x2)
			return 1;
		break;
	case UP:
		if (x1 == x2 && (y1 + 1) == y2)
			return 1;
		break;
	case DOWN:
		if (x1 == x2 && (y1 - 1) == y2)
			return 1;
		break;
	}
	return 0;
}

int can_move(int direction, int x, int y) {
	switch(direction) {
	case LEFT:		
		if (x <= 1 ) return 0;
		break;
	case RIGHT:
		if (x >= MW - 2) return 0;		
		break;
	case UP:
		if (y <= 1) return 0;
		break;
	case DOWN:
		if (y >= MW - 2) return 0;
		break;
	}
	return 1;
}

void move_obj(int direction, int& x, int& y) {
	switch(direction) {
	case LEFT:
		x -= 1;
		break;
	case RIGHT:
		x += 1;
		break;
	case UP:
		y -= 1;
		break;
	case DOWN:
		y += 1;
		break;
	}
}

void move(int direction) {
	if (is_front(direction, bx, by, px, py ))
		if(can_move(direction, bx, by)) {
			move_obj(direction, bx, by);
			move_obj(direction, px, py);
		}
		else
			return;
	else if (can_move(direction, px, py))
		move_obj(direction, px,py);
}			

void updateGame(int direction) {
	map[py][px] = 0;	
	map[by][bx] = 0;		
	
	move(direction);	

	map[py][px] = PLAYER;
	map[by][bx] = BALL;	
	map[ey][ex] = EXIT;
}

void draw() {
	int i, j;
	system("cls");
	for( i = 0; i < MW; i++) {
		for( j = 0; j < MW; j++) {
			switch(map[i][j]) {
				case WALL:
					printf("*");
					break;
				case PLAYER:
					printf("P");
					break;
				case BALL:
					printf("O");
					break;
				case EXIT:
					printf("X");
					break;
				default:
					printf(" ");
			}			
		}
		printf("\n");
	}
	std::cout << "\nTurn: "<<  turn << std::endl;
	std::cout << "Press r to reset,or esc to end." << std::endl;
}