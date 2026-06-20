#include<stack>
#include"Location2D.h"
#include <iostream>
#include <deque>
using namespace std;

const int  MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

bool isValidLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
	else return map[r][c] == '0' || map[r][c] == 'x';
}

////1번 stack dfs
//int main(){
//	stack<Location2D> locStack;
//	Location2D entry(1, 0);
//	locStack.push(entry);
//
//	while (locStack.empty() == false) {
//		Location2D here = locStack.top();
//		locStack.pop();
//
//		int r = here.row, c = here.col;
//		printf("(%d, %d)",r,c);
//		if (map[r][c] == 'x') {
//			printf("미로 탐색 성공 \n");
//			return 0;
//		}
//		else{
//			map[r][c] = '.';
//			if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
//			if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
//			if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
//			if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
//			}
//	}
//	printf("미로 탐색 실패\n");
//	return 0;
//}



////2번 deque dfs
//int main() {
//	deque<Location2D> locDeque;
//	Location2D entry(1, 0);
//	locDeque.push_front(entry);
//
//	while (locDeque.empty() == false) {
//		Location2D here = locDeque.front();
//		locDeque.pop_front();
//		
//		int r = here.row, c = here.col;
//		printf("(%d, %d)", r, c);
//		if (map[r][c] == 'x') {
//			printf("미로 탐색 성공 \n");
//			return 0;
//		}
//
//		else {
//			map[r][c] = '.';
//			if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
//			if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
//			if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
//			if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
//		}
//	}
//	printf("미로탐색실패 \n");
//	return 0;
//}



//3번 deque bfs
int main() {
	deque<Location2D> locDeque;
	Location2D entry(1, 0);
	locDeque.push_back(entry);

	while (locDeque.empty() == false) {
		Location2D here = locDeque.front();
		locDeque.pop_front();

		int r = here.row, c = here.col;
		printf("(%d, %d)", r, c);
		if (map[r][c] == 'x') {
			printf("미로 탐색 성공 \n");
			return 0;
		}

		else {
			map[r][c] = '.';
			if (isValidLoc(r - 1, c)) locDeque.push_back(Location2D(r - 1, c));
			if (isValidLoc(r + 1, c)) locDeque.push_back(Location2D(r + 1, c));
			if (isValidLoc(r, c - 1)) locDeque.push_back(Location2D(r, c - 1));
			if (isValidLoc(r, c + 1)) locDeque.push_back(Location2D(r, c + 1));
		}
	}
	printf("미로탐색실패 \n");
	return 0;
}