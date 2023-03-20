#pragma once



class Rat {
public:
	Rat() {};
	Rat(double x, double y, double degrees);
	void Scurry(Maze& m, double DT, bool backwards = false);
	void SpinLeft(double DT);
	void SpinRight(double DT);
	void Draw();
	void SetX(double x) { mX = x; };
	void SetY(double y) { mY = y; };
	void SetDegrees(double degrees) { mDegrees = degrees;};
	void SetPosition(double x, double y, double deg);
	double GetX() { return mX; };
	double GetY() { return mY; };
	double GetDX(double DT);
	double GetDY(double DT);
private:
	double mX = 0, mY = 0, mDegrees = 0;
	double mSpinSpeed = .4, mMoveSpeed = 0.004;
	double ratsRadius = 0.2;
};