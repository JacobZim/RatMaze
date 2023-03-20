
#include <vector>
#include <iostream>
#include "glut.h"
#include "Maze.h"
#include "graphics.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Textures
const int num_textures = 2;
unsigned int texName[num_textures];

void InitializeMyStuff1()
{
	const char max_file_size = 100;
	char imageFiles[num_textures][max_file_size] = { "sandra880.jpg", "brick.jpg" };

	glGenTextures(num_textures, texName);

	for (int i = 0; i < num_textures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(imageFiles[i], &width, &height, &nrChannels, 0);
		if (data)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			// NOTE: If the above command doesn't work, try it this way:
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				//glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
}

void Cell::Draw(int i, int j) {
	if (current_view == top_view) {
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
	} else {
		if (t) {
			/*
			unsigned char r = (unsigned char)((i * 34253 + j * 45563) % 256);
			unsigned char g = (unsigned char)((i * 97654 + j * 36721) % 256);
			unsigned char b = (unsigned char)((i * 67467 + j * 22345) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i, j + 1, 0);
			glVertex3d(i + 1, j + 1, 0);
			glVertex3d(i + 1, j + 1, 1);
			glVertex3d(i, j + 1, 1);
			glEnd();
			*/
			
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, texName[1]); // Sandra

			glBegin(GL_QUADS);
			glTexCoord2f(0, 4); glVertex3d(i, j + 1, 0); // All of Sandra
			glTexCoord2f(4, 4); glVertex3d(i + 1, j + 1, 0);
			glTexCoord2f(4, 0); glVertex3d(i + 1, j + 1, 1);
			glTexCoord2f(0, 0); glVertex3d(i, j + 1, 1);
			glEnd(); // GL_QUADS
			glDisable(GL_TEXTURE_2D);
		}
		if (r) {
			/*
			unsigned char r = (unsigned char)((i * 34253 + j * 45563) % 256);
			unsigned char g = (unsigned char)((i * 97654 + j * 36721) % 256);
			unsigned char b = (unsigned char)((i * 67467 + j * 22345) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i + 1, j + 1, 0);
			glVertex3d(i + 1, j, 0);
			glVertex3d(i + 1, j, 1);
			glVertex3d(i + 1, j + 1, 1);
			glEnd();*/
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, texName[1]); // Sandra

			glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex3d(i + 1, j + 1, 0); // All of Sandra
			glTexCoord2f(1, 1); glVertex3d(i + 1, j, 0);
			glTexCoord2f(1, 0); glVertex3d(i + 1, j, 1);
			glTexCoord2f(0, 0); glVertex3d(i + 1, j + 1, 1);
			glEnd(); // GL_QUADS
			glDisable(GL_TEXTURE_2D);
		}
		if (j == 0 && b) {
			/*
			unsigned char r = (unsigned char)((i * 34253 + j * 45563) % 256);
			unsigned char g = (unsigned char)((i * 97654 + j * 36721) % 256);
			unsigned char b = (unsigned char)((i * 67467 + j * 22345) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i, j, 0);
			glVertex3d(i + 1, j, 0);
			glVertex3d(i + 1, j, 1);
			glVertex3d(i, j, 1);
			glEnd(); */
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, texName[0]); // Sandra

			glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex3d(i, j, 0); // All of Sandra
			glTexCoord2f(1, 1); glVertex3d(i + 1, j, 0);
			glTexCoord2f(1, 0); glVertex3d(i + 1, j, 1);
			glTexCoord2f(0, 0); glVertex3d(i, j, 1);
			glEnd(); // GL_QUADS
			glDisable(GL_TEXTURE_2D);
		}
		if (i == 0) {
			/*
			unsigned char r = (unsigned char)((i * 34253 + j * 45563) % 256);
			unsigned char g = (unsigned char)((i * 97654 + j * 36721) % 256);
			unsigned char b = (unsigned char)((i * 67467 + j * 22345) % 256);
			glColor3ub(r, g, b);
			glBegin(GL_QUADS);
			glVertex3d(i, j, 0);
			glVertex3d(i, j + 1, 0);
			glVertex3d(i, j + 1, 1);
			glVertex3d(i, j, 1);
			glEnd(); */
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, texName[0]); // Sandra

			glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex3d(i, j, 0); // All of Sandra
			glTexCoord2f(1, 1); glVertex3d(i, j + 1, 0);
			glTexCoord2f(1, 0); glVertex3d(i, j + 1, 1);
			glTexCoord2f(0, 0); glVertex3d(i, j, 1);
			glEnd(); // GL_QUADS
			glDisable(GL_TEXTURE_2D);
		}
	}
}

Maze::Maze() {
}

void Maze::Initialize() {
	RemoveWalls(0, 0);
	InitializeMyStuff1();

	// Knock out 1 bottom wall and 1 top wall
	mStartX = rand() % mW;
	mEndX = rand()*rand() % mW;
	mCells[mStartX][0].b = false;
	mCells[mEndX][mH - 1].t = false;
	//mRat.SetPosition(mStartX + 0.5, 0.5, 0);
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

/*void Maze::DrawRat() {
	mRat.Draw();
}**/

int Maze::GetStartX() {
	return mStartX;
}
int Maze::GetEndX() {
	return mEndX;
}

bool Maze::IsSafe(double x, double y, double radius) {
	int cellX = (int)x;
	int cellY = (int)y;
	double offsetX = x - cellX;
	double offsetY = y - cellY;
	// Check right wall of current cell
	if ((mCells[cellX][cellY].r) && (offsetX + radius >= 1.0)) 
		return false;
	// Check left wall
	if (mCells[cellX][cellY].l && (offsetX - radius <= 0.0))
		return false;
	// Check top wall of current cell
	if ((mCells[cellX][cellY].t) && (offsetY + radius >= 1.0))
		return false;
	// Check bottom wall
	if (mCells[cellX][cellY].b && (offsetY - radius <= 0.0))
		return false;
	
	// check right bottom corner
	if (offsetX + radius >= 1.0 && offsetY - radius <= 0)
		return false;
	// check left bottom corner
	if (offsetX - radius <= 0.0 && offsetY - radius <= 0)
		return false;
	// check right top corner
	if (offsetY + radius >= 1.0 && offsetX + radius >= 1.0)
		return false;
	// check left top corner
	if (offsetY + radius >= 1.0 && offsetX - radius <= 0)
		return false;

	return true;
}