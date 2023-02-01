
#include <vector>
#include "glut.h"
#include "Maze.h"

void Cell::Draw(int i, int j) {
	if (l) {
		glBegin(GL_LINES);
		glVertex2d(i, j);
		glVertex2d(i, j + 1);
		glEnd();
	}
	if (b) {
		glBegin(GL_LINES);
		glVertex2d(i, j);
		glVertex2d(i + 1, j);
		glEnd();
	}
	if (r) {
		glBegin(GL_LINES);
		glVertex2d(i + 1, j);
		glVertex2d(i + 1, j + 1);
		glEnd();
	}
	if (t) {
		glBegin(GL_LINES);
		glVertex2d(i, j + 1);
		glVertex2d(i + 1, j + 1);
		glEnd();
	}
}

Maze::Maze() {
	
	// Knock out 1 bottom wall and 1 top wall
}

void Maze::Initialize() {
	RemoveWalls(0, 0);
}

void Maze::RemoveWalls(int i, int j) {
	mCells[i][j].visited = true;
	enum class direction { LEFT, UP, RIGHT, DOWN };

	while (true) {
		std::vector<direction> move;

		// Can we go left?
		if ((i - 1 >= 0) && !mCells[i - 1][j].visited)
			move.push_back(direction::LEFT);
		if ((j + 1 < N) && !mCells[i][j + 1].visited)
			move.push_back(direction::UP);
		if ((i + 1 < M) && !mCells[i + 1][j].visited)
			move.push_back(direction::RIGHT);
		if ((j - 1 >= 0) && !mCells[i][j - 1].visited)
			move.push_back(direction::DOWN);

		if (move.size() == 0)
			return; //no possible moves forward

		int r = rand() % move.size();

		if (move[r] == direction::LEFT) {
			mCells[i][j].l = false;
			mCells[i - 1][j].r = false;
			RemoveWalls(i - 1, j);
		} else if (move[r] == direction::RIGHT) {
			mCells[i][j].r = false;
			mCells[i+1][j].l = false;
			RemoveWalls(i + 1, j);
		} else if (move[r] == direction::UP) {
			mCells[i][j].t = false;
			mCells[i][j+1].b = false;
			RemoveWalls(i, j + 1);
		} else if (move[r] == direction::DOWN) {
			mCells[i][j].b = false;
			mCells[i][j - 1].t = false;
			RemoveWalls(i, j - 1);
		}

	}
}

void Maze::Draw() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			mCells[i][j].Draw(i, j);
		}
	}
}