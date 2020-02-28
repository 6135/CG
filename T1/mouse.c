void idle()
{
if (!mouseDown)
{
xrot += 0.3f;
yrot += 0.4f;
}

glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
switch(key)
{
case 27 :
exit(1); break;
}
}

void specialKeyboard(int key, int x, int y)
{
if (key == GLUT_KEY_F1)
{
fullscreen = !fullscreen;

if (fullscreen)
glutFullScreen();
else
{
glutReshapeWindow(500, 500);
glutPositionWindow(50, 50);
}
}
}

void mouse(int button, int state, int x, int y)
{
if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
{
mouseDown = true;

xdiff = x - yrot;
ydiff = -y + xrot;
}
else
mouseDown = false;
}

void mouseMotion(int x, int y)
{
if (mouseDown)
{
yrot = x - xdiff;
xrot = y + ydiff;

glutPostRedisplay();
}
}
