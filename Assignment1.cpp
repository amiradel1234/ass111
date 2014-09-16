#include "stdafx.h"
#include "stdio.h"
#include "glut.h"

void display(void);
void scaleTriangle(float vertices[6], int position);
void drawTriangles(float vertices[6], int order);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);

float tempVertices[6];
float vertices[6] = {300.0f, 100.0f, 800.0f, 100.0f, 550.0f, 500.0f};
int clicks = 0;
int order = 0;
float angle = 0.0f;

void main(int argc, char** argr)
{
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Sierpinski Triangles");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	gluOrtho2D(0.0,1000.0,0.0,600.0);
	glutMainLoop();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
	drawTriangles(vertices, order);
	glEnd();

	glPopMatrix();
	glFlush();
}

void scaleTriangle(float vertices[6], int position) 
{
	float dx = 0.5f * vertices[position * 2];
	float dy = 0.5f * vertices[position * 2 + 1];
	for (int i = 0; i < 6; i = i + 2) 
	{
		vertices[i] = (0.5f * vertices[i]) + dx;
		vertices[i + 1] = (0.5f * vertices[i + 1]) + dy;
	}
}

void drawTriangles(float vertices[6], int order) 
{
	if (order == 0)
	{
		glVertex3f(vertices[0], vertices[1], 0.0f);
		glVertex3f(vertices[2], vertices[3], 0.0f);
		glVertex3f(vertices[4], vertices[5], 0.0f);
		return;
	} 
	float vertices1[6] = {vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5]};
	scaleTriangle(vertices1, 0);
	drawTriangles(vertices1, order - 1);

	float vertices2[6] = {vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5]};
	scaleTriangle(vertices2, 1);
	drawTriangles(vertices2, order - 1);

	float vertices3[6] = {vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5]};
	scaleTriangle(vertices3, 2);
	drawTriangles(vertices3, order - 1);
}

void keyboard(unsigned char key, int mouseX, int mouseY)
{
	switch(key) 
	{
		case '0' : order = 0; break;
		case '1' : order = 1; break;
		case '2' : order = 2; break;
		case '3' : order = 3; break;
		case '4' : order = 4; break;
		case '5' : order = 5; break;
		case '6' : order = 6; break;
		case 'r' : 
			glRotatef(-angle, 0.0f, 0.0f, 1.0f);
			glTranslatef(5.0f, 0.0f, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			break;
		case 'l' : 
			glRotatef(-angle, 0.0f, 0.0f, 1.0f);
			glTranslatef(-5.0f, 0.0f, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			break;
		case 'u' : 
			glRotatef(-angle, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, 5.0f, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			break;
		case 'd' : 
			glRotatef(-angle, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, -5.0f, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			break;
		case 'o' : glRotatef(1.0f, 0.0f, 0.0f, 1.0f); angle++; break;
		case 'b' : glScalef(1.1f, 1.1f, 1.0f); break;
		case 's' : glScalef(0.9f, 0.9f, 1.0f); break;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		tempVertices[clicks * 2] = x;
		tempVertices[clicks * 2 + 1] = 600 - y;
		if (clicks == 2) 
		{
			memcpy(vertices, tempVertices, 6 * sizeof(int));
			glutPostRedisplay();
		}
		clicks = (clicks + 1) % 3;
	}
}

