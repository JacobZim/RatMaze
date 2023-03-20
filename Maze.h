#pragma once


//need an initializer to randomly seed and break the walls
// not in main function

const int M = 12;
const int N = 10;


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
	int GetEndX();
	bool IsSafe(double x, double y, double radius);
	/*
	void DrawRat();
	void MoveRat(double dt, bool backwards = false) { mRat.Scurry(*this, dt, backwards); };
	void TurnRatRight(double dt) { mRat.SpinRight(dt); };
	void TurnRatLeft(double dt) { mRat.SpinLeft(dt); };*/
private:
	Cell mCells[M][N];
	int mStartX = 0, mEndX = 0;
	int mW = M, mH = N;
};