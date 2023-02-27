#pragma once
#include <cmath>
#include <cstring>
#include <ctime>
#include "glut.h"

// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius);
void DrawRectangle(double x1, double y1, double x2, double y2);

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char* string);

double GetDeltaTime();