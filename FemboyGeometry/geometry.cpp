#include "geometry.h"

GeometryPlayer::GeometryPlayer(int width, int height)
	: m_width(width), m_height(height), m_theta(0.0f), m_tickCounter(0), m_rotCounter(0), m_mode(0)
{
	/* select clearing (background) color */
    glClearColor(0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/20.0, width/20.0, -height/20.0, height/20.0, -height/20.0, height/20.0);
}

GeometryPlayer::~GeometryPlayer()
{
	glutDestroyWindow(glutGetWindow());
}

void GeometryPlayer::nextMode()
{
	m_tickCounter = 0;
	m_rotCounter = 0;
	m_theta = 0;
	m_mode = (m_mode + 1) % NUM_MODES;
}

void GeometryPlayer::animateBezier()
{
	/* draw based bezier curves */
	glPushMatrix();
		glRotatef(m_theta/4.0f, 0.0, 0.0, 1.0);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (int x = 20; x >= 0; --x)
		{
			int y = 20 - x;
			glVertex2i(x, 0);
			glVertex2i(0, y);
			glVertex2i(-x, 0);
			glVertex2i(0, -y);
			glVertex2i(-x, 0);
			glVertex2i(0, y);
			glVertex2i(x, 0);
			glVertex2i(0, -y);
		}
		glEnd();
	glPopMatrix();
}

void GeometryPlayer::animateCone()
{
	/* draw based cone */
	float radius = 7.5f;
	glPushMatrix();
		glRotatef(m_theta, 0.0, 1.0, 0.5);
		glColor3f(1.0, 1.0, 0.0);
		int circle_points = 10;
		glutWireCone(radius, 15.0f, 10, circle_points);
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		// draw wires through the circle
			for (int i = 0; i < circle_points; i++)
			{ 
				float angle = 2*PI*i/circle_points;
				float x = radius*cos(angle);
				float y = radius*sin(angle);
				// circumference should be drawn too, so alternate the order of the vertices
				if (i % 2 == 0)
				{
					glVertex2f(x, y);
					glVertex2f(-x, -y);
				}
				else
				{
					glVertex2f(-x, -y);
					glVertex2f(x, y);
				}
			}
		glEnd();
	glPopMatrix();
}

void GeometryPlayer::animateCube()
{
	/* draw based colorful cube */
	glPushMatrix();
		glRotatef(m_theta, 1.0, 0.5, 0.0);
		glColor3f(0.0, 1.0, 1.0);
		// MOAR WIRES
		for (int i = 0; i < 5; ++i)
		{
			glutWireCube(i*2);
		}
	glPopMatrix();
}

void GeometryPlayer::animateGlobe()
{
	/* draw based wireframe sphere with rotation animation */
	glPushMatrix();
		glRotatef(m_theta, 0.0, 1.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glutWireSphere(10.0, 15, 15);
	glPopMatrix();
}

void GeometryPlayer::animateTorus()
{
	/* draw based (ford) torus */
	glPushMatrix();
		glRotatef(60.0f, 1.0, 0.0, 0.0);
		glRotatef(m_theta, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		glutWireTorus(2.0, 10.0, 10, 15);
	glPopMatrix();
}

void GeometryPlayer::display()
{
	/* clear all pixels */
    glClear(GL_COLOR_BUFFER_BIT);

	switch (m_mode)
	{
	case 0:
		animateGlobe();
		break;
	case 1:
		animateCube();
		break;
	case 2:
		animateTorus();
		break;
	case 3:
		animateBezier();
		break;
	case 4:
		animateCone();
		break;
	}

/*  don't wait!
 *  start processing buffered OpenGL routines
 */
    glutSwapBuffers();
}

void GeometryPlayer::tick(int)
{
	m_theta += OMEGA;
	++m_tickCounter;
	float angle = m_theta - m_rotCounter * 360.0f;
	if (angle > 360.0f && ++m_rotCounter == 5)
		nextMode();
	glutPostRedisplay();
}
