#include <cmath>
#include "glut.h"
#include "Maze.h"
#include "Rat.h"
#include "HelperFunctions.h"


Rat::Rat(double x, double y, double degrees) {
	mX = x;
	mY = y;
	mDegrees = degrees;
}

void Rat::Scurry( Maze & m, double DT, bool backwards ) {
	double radians = mDegrees / 180 * 3.14;// / 15926;
	if (backwards == true) {
		radians += 3.14;
	}
	double dx = cos(radians) * mMoveSpeed * DT;
	double dy = sin(radians) * mMoveSpeed * DT;
	
	double newX = mX + dx;
	double newY = mY + dy;

	if (m.IsSafe(newX, newY, ratsRadius)) {
		mX = newX;
		mY = newY;
	}
	else if (m.IsSafe(mX, newY, ratsRadius)) {
		mY = newY;
	}
	else if (m.IsSafe(newX, mY, ratsRadius)) {
		mX = newX;
	}
}

void Rat::SpinLeft(double DT) {
	mDegrees += mSpinSpeed * DT;
	if (mDegrees >= 360) {
		mDegrees = (int)mDegrees % 360;
	}
}

void Rat::SpinRight(double DT) {
	mDegrees -= mSpinSpeed * DT;
	while (mDegrees < 0) {
		mDegrees = mDegrees + 360;
	}
	if (mDegrees >= 360) {
		mDegrees = (int)mDegrees % 360;
	}
}

void Rat::SetPosition(double x, double y, double deg) {
	SetX(x);
	SetY(y);
	SetDegrees(deg);
}


void Rat::Draw() {
	
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated(mDegrees, 0, 0, 1);
	//DrawTriangle(.3, 0, -.2, -.2, -.2, .2);
	
	glColor3d(.7, .5, .2);
	DrawCircle(.12, .12, .05);
	DrawCircle(-.12, .12, .05);
	DrawCircle(.12, -.12, .05);
	DrawCircle(-.12, -.12, .05);
	glColor3d(.775,.775,.775);
	//DrawRectangle(-.2, .1, .1, -.1);
	DrawTriangle(.1, .1, .26, 0, .1, -.1);
	glColor3d(.85,.85,.85);
	DrawCircle(0, 0, .19);
	glColor3d(.7, .5, .2);
	DrawRectangle(-.3, .025, -.15, -.025);
	DrawRectangle(.22, .1, .23, -.1);
	DrawRectangle(.2, .11, .21, -.11);
	glPopMatrix();
}



//bitblit for using an image