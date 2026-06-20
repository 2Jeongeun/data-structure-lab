#include <deque>
#include "Location2D.h"
using namespace std;

void main() {
	deque<Location2D> locDeque;
	Location2D entry(1, 0);
	locDeque.push_front(entry);

	while (locDeque.empty() = false) {
		Location2D here = locDeque.front();
		locDeque.pop_front();

		else {
			map[r][c] = '.';
			if (ifValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
			if (ifValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
			if (ifValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
			if (ifValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
		}
	}
	printf("미로탐색실패 \n");
}