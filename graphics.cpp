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
#include "glut.h"
#include "Maze.h"
#include "Rat.h"
#include "HelperFunctions.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;


Maze gMaze;
Rat gRat;
bool gMoveForward = false;
bool gMoveBackwards = false;
bool gTurnRight = false;
bool gTurnLeft = false;
double gSpeed = .001;




//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

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

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
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
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


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
	glutInit(&argc, argv);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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
