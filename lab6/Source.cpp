#define _USE_MATH_DEFINES
//Подключаем библиотеку glut.h и cmath
#include <GL\glut.h>
#include <cmath>
#include<iostream>
using namespace std;

double N = 0;
double k = 8987551777;
double e = 1.6021892 * pow(10, -19);
double M = 6.638 * pow(10, -27);
double Z = 2;
double dt = 1;
double t;
double F = 2 * k*Z*e*e / M;
//double x0 = -3;
//double y0 = 0.1;
double x = -3;
double y = 0.5;
double dx_dt = 3;
double dy_dt = 0;
double x_pred, y_pred;


double dv_dt1=3;
double dv_dt2=3;



void change_size(GLsizei w, GLsizei h) {
	GLdouble aspect_ratio;
	//Предотвращается деление на 0 
	if (h == 0)
		h = 1;
	//Устанавливается поле просмотра с размерами окна 
	glViewport(0, 0, w, h);
	//Обновляется система координат 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//С помощью плоскостей отсечения (левая, правая, нижняя, //верхняя, ближняя, дальняя) устанавливается объем отсечения 
	aspect_ratio = (GLdouble)w / (GLdouble)h;
	gluPerspective(150.0, aspect_ratio, 1, 100.0);
	glTranslatef(0.0, 0.0, -12.0);
	//glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
	//gluLookAt(0, 0, 150, 0, 0, 0, 0, 1, 0);

	/*
	if (w <= h)
		glOrtho(-40.0, 6.0, -23.0 / aspect_ratio, 23.0 / aspect_ratio, -1.0, 1.0);
	else
		glOrtho(-40.0*aspect_ratio, 6.0*aspect_ratio, -23.0, 23.0, -1.0, 1.0);
	*/
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void initialise() {
	//Задается цвет очистки окна - черный
	glClearColor(0.0, 0.0, 0.0, 0.0);
}



void render_scene() {
	//Очищается окно, используя текущий цвет очистки 
	glClear(GL_COLOR_BUFFER_BIT);
	//В качестве текущего цвета рисования задаем красный 
	//R G B 
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1);
	//Рисуем координатную систему:
	//Рисуем ось Ox
	glBegin(GL_LINES);
	glVertex2f(-39.0, 0.0);
	glVertex2f(5.0, 0.0);
	glEnd();
	//Рисуем ось Оу 
	glBegin(GL_LINES);
	glVertex2f(0.0, -22.0);
	glVertex2f(0.0, 22.0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0, -22.0, -22.0);
	glVertex3f(0.0, 22.0, 22.0);
	glEnd();
	
	//Задаем в качества цвета закраски синий 
	glColor3f(1.0, 1.0, 1.0);
	//Рисуем траекторию первого спутника 
	glPointSize(3);
	//glLineWidth(10);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	t = 0;
	//while (t <= N) {
	x = -5;
	y = 0.5;
	for (t = 0; t <= N; t += dt) {
		x_pred = x;
		y_pred = y;

		dv_dt1 = dv_dt1 + F * (x / pow((x*x + y * y), 1.5)) * dt;
		x = x + (dv_dt1 * dt);

		dv_dt2 = dv_dt2 + F * (y / pow((x*x + y * y), 1.5)) * dt;
		y = y + (dv_dt2 * dt);

		
		
		
	}
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(x_pred, y_pred);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3d(x, y, 0);
	glEnd();


	
	glutSwapBuffers();
	//Очищаем очередь текущих команд 
	glFlush();
}


void keyboard_func(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		N += 0.1;
		if (N < 10000) render_scene();
		break;
	case 'z':
		N += 1;
		if (N < 10000) render_scene();
		break;
	case 'c':
		N += 0.01;
		if (N < 10000) render_scene();
		break;
	case 27:	// Escape key
		exit(0);
	}
}

static void reshape_view(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Rutherford's experiments");

	//glEnable(GL_DEPTH_TEST);
	glRotatef(45.0, 0.0, 0.0, 0.0);

	glutKeyboardFunc(keyboard_func);
	glutDisplayFunc(render_scene);
	glutReshapeFunc(change_size);
	initialise();
	glutMainLoop();
	return 0;
}