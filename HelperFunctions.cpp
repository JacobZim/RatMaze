#pragma once
#include <cmath>
#include <cstring>
#include <ctime>
#include "glut.h"

// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char* string)
{
	void* font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glDisable(GL_BLEND);
}

double GetDeltaTime()
{
	static clock_t start_time = clock();
	static int current_frame = 0;
	clock_t current_time = clock();
	current_frame += 1;
	double total_time = double(current_time - start_time) / CLOCKS_PER_SEC;
	if (total_time == 0)
		total_time = .00001;
	double frames_per_second = (double)current_frame / total_time;
	double DT = 1.0 / frames_per_second * 500;
	return DT;
}