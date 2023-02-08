#pragma once

//need an initializer to randomly seed and break the walls
// not in main function


const int M = 6;
const int N = 5;

class Cell {
public:
	Cell() {
		l = t = r = b = true;
		visited = false;
	}
	void Draw(int i, int j);
	bool l, t, r, b, visited;
private:

};

class Maze {
public:
	Maze();
	void Draw();
	void RemoveWalls(int i, int j);
	void Initialize();
	int GetStartX();
	bool IsSafe(double x, double y, double radius);
private:
	Cell mCells[M][N];
};