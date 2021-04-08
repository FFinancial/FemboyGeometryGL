#include <GL/glut.h>
#include "geometry.h"

#define WIN_WIDTH	640
#define WIN_HEIGHT	480
#define FPS			60
#define TITLE		"FemboyGeometry (OpenGLel Edition)"

GeometryPlayer* g_player = NULL;

void mouse(int button, int state, int, int)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
			g_player->nextMode();
		else if (button == GLUT_RIGHT_BUTTON)
			delete g_player;
	}
}

void display(void)
{
	g_player->display();
}

void tick(int arg)
{
	g_player->tick(arg);
	glutTimerFunc(1000.0/FPS, tick, 0);
}

/* 
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(TITLE);

    g_player = new GeometryPlayer(WIN_WIDTH, WIN_HEIGHT);
    glutDisplayFunc(display);
	glutMouseFunc(mouse);
	tick(0);

    glutMainLoop();
	delete g_player;
    return 0;
}
