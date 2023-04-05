// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.
#pragma once

#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include "glut.h"
#include "Maze.h"
#include "Rat.h"
#include "HelperFunctions.h"
#include "graphics.h"


// Global Variables (Only what you need!)

double screen_x = 700;
double screen_y = 500;

viewtype current_view = top_view;

Maze gMaze;
Rat gRat;
bool gMoveForward = false;
bool gMoveBackwards = false;
bool gTurnRight = false;
bool gTurnLeft = false;
double gSpeed = .001;

// global types and variable:



//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (current_view == perspective_view)
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gluLookAt(-3, -3, 12, 4.5, 4, 0, 0, 0, 1);
	}	//camera position, point looking at, tilt
	else if (current_view == top_view)
	{
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else // current_view == rat_view
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		double z_level = .25; //rat.GetZ(x,y);
		double x = gRat.GetX();
		double y = gRat.GetY();
		double dx = 50*gRat.GetDX(GetDeltaTime()); //2*rat.GetDXUnscaled()
		double dy = 50*gRat.GetDY(GetDeltaTime()); //2*rat.GetDYUnscaled()
		double at_x = x + dx;
		double at_y = y + dy;
		//float z2 = rat.GetZ(at_x, at_y);
		//float downward_tilt = .30;
		double at_z = .26; //z2 - downward_tilt
		gluLookAt(x, y, z_level, at_x, at_y, at_z, 0, 0, 1);
	}

	if (gMoveForward) {
		gRat.Scurry(gMaze, GetDeltaTime());
	}
	if (gMoveBackwards) gRat.Scurry(gMaze, GetDeltaTime(), true);
	if (gTurnLeft) gRat.SpinLeft(GetDeltaTime());
	else if (gTurnRight) gRat.SpinRight(GetDeltaTime());
	// Test lines that draw all three shapes and some text.
	// Delete these when you get your code working.
	glColor3d(0,0,1);
	
	//Draw the rat, make your own class with Rat.Draw()
	//Make a method to find start cell and calculate starting position
	//Code_keys.cpp/.h available for download
	

	glColor3d(0,0,0);
	gMaze.Draw();
	gRat.Draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboardup(unsigned char c, int x, int y) 
{
	switch (c)
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;
		case 'b':
			// do something when 'b' character is hit.
			break;
		case 'w':
			gMoveForward = false;
			break;
		case 'a':
			gTurnLeft = false;
			break;
		case 's':
			gMoveBackwards = false;
			break;
		case 'd':
			gTurnRight = false;
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}




void SetTopView(int w, int h)
{
	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, M + world_margin_x,
		-world_margin_y, N + world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}

void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 38.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ .1, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}

void SetRatView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 120.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ 0.1, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}


// reshape:
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);

	if (current_view == top_view)
	{
		SetTopView(w, h);
	}
	else if (current_view == perspective_view)
	{
		SetPerspectiveView(w, h);
	}
	else if (current_view == rat_view)
	{
		SetRatView(w, h);
	}
}
/*
// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-.5, M+0.5, -.5, N+.5);
	glMatrixMode(GL_MODELVIEW);

}*/

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27: // escape character means to quit the program
		exit(0);
		break;
	case 'w':
		gMoveForward = true;
		break;
	case 'a':
		gTurnLeft = true;
		break;
	case 's':
		gMoveBackwards = true;
		break;
	case 'd':
		gTurnRight = true;
		break;
	case 'b':
		// do something when 'b' character is hit.
		break;
	case 'r':
		current_view = rat_view;
		SetRatView(screen_x, screen_y);
		break;
	case 'p':
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
		break;
	case 't':
		current_view = top_view;
		SetTopView(screen_x, screen_y);
		break;
	default:
		return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		gTurnLeft = true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		gTurnLeft = false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
		gMoveForward = true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
		gMoveForward = false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		gTurnRight = false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gTurnRight = true;
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	srand(time(0));
	gMaze.Initialize();
	gRat.SetPosition(gMaze.GetStartX() + 0.5, 0.5, 0);

}


int main(int argc, char **argv)
{
	//PlaySOund("file.wav", NULL, ASync); include windows.h
	glutInit(&argc, argv);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	//int id1, id2;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("This appears in the title bar");
		// id2 = glutCreateWindow("Second window");
	}

	//glutSetWindow(id2);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}


/*
void AdjustWaterHeight(double t) {
	waterHeight = -2 + .2 * sin(t);
}

void DrawMap() {
	




	//Draw Water
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4d(0.1, 0.2, 0.9, 0.8;
	//Draw really big rect
*/