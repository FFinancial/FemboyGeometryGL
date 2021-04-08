#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

#define PI 3.14159
#define NUM_MODES 5
#define OMEGA 4.0f


class GeometryPlayer
{
public:
	GeometryPlayer(int width, int height);
	~GeometryPlayer();

	void nextMode(void);
	void display(void);
	void tick(int);

protected:
	void animateBezier(void);
	void animateCone(void);
	void animateCube(void);
	void animateGlobe(void);
	void animateTorus(void);

private:
	int m_width;
	int m_height;
	float m_theta;
	int m_tickCounter;
	int m_rotCounter;
	int m_mode;
};
