#include <cmath>
#include "glut.h"
#include "Maze.h"
#include "Rat.h"


void Rat::Rat(double x, double y, double degrees) {

}

void Rat::ScurryForward(double DT, Maze & m) {
	double radians = mDegrees / 180 * 3.14 / 15926;
	double speed = 1.1;
	double dx = cos(radians) * speed * DT;
	double dy = sin(radians) * speed * DT;
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
	double speed = 150.0;
	mDegrees += speed * DT;
}

void Rat::SpinRight(double DT) {
	double speed = 150.0;
	mDegrees -= speed * DT;
}

void Rat::Draw() {
	glColor3d(1, 0, 0);
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated(mDegrees, 0, 0, 1);
	glDrawTriangle
}

//bitblit for using an image