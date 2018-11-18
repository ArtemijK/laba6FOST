//SECOND
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
double Z = 2.0;
double dt = 0.01;
double t=0;
double F = 2 * k*Z*e*e / M;
//double x0 = -3;
//double y0 = 0.1;
double x = -20;
double y = 0.5;
double dx_dt = 0;
double dy_dt = 0;
double x_pred, y_pred;


double dv_dt1=3;
double v1=0;
double h1=0;
double tau1=0;
double dv_dt2=0;
double v2=0;
double h2=0;
double tau2=0;


double velo(double v1, double h1, double tau1) {
	dv_dt1 = dv_dt1 + F * (v1 / pow(sqrt(v1*v1 + h1 * h1), 3)) * tau1;

	v1 = v1 + (dv_dt1 * tau1);

	return v1;
}

double velo2(double v2, double h2, double tau2) {
	dv_dt2 = dv_dt2 + F * (v2 / pow(sqrt(v2*v2 + h2 * h2), 3)) * tau2;

	v2 = v2 + (dv_dt2 * tau2);

	return v2;
}

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
	glRotatef(15.0f, 1.0f, 1.0f, 1.0f);
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
	x = -15;
	y = 0.7;
	for (t = 0; t <= N; t += dt) {
		x_pred = x;
		y_pred = y;
		dv_dt1 = dv_dt1 + F * (x / pow(sqrt(x*x + y * y), 3)) *dt;

		x = x + (dv_dt1 * dt);

		dv_dt2 = dv_dt2 + F * (y / pow(sqrt(y*y + x * x), 3)) * dt;

		y = y + (dv_dt2 * dt);
		//x = velo(x_pred, y_pred, dt);
		//cout << x << endl;
		//y = velo2(x_pred, y_pred, dt);
		//cout << y << endl;
		
		
	}
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(x_pred, y_pred);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2d(x, y);
	glEnd();


	glBegin(GL_POINTS);
	t = 0;
	//while (t <= N) {
	x = -15;
	y = 0.5;
	dv_dt1 = 3;
	dv_dt2 = 0;
	for (t = 0; t <= N; t += dt) {
		x_pred = x;
		y_pred = y;
		dv_dt1 = dv_dt1 + F * (x / pow(sqrt(x*x + y * y), 3)) *dt;

		x = x + (dv_dt1 * dt);

		dv_dt2 = dv_dt2 + F * (y / pow(sqrt(y*y + x * x), 3)) * dt;

		y = y + (dv_dt2 * dt);
		//x = velo(x_pred, y_pred, dt);
		//cout << x << endl;
		//y = velo2(x_pred, y_pred, dt);
		//cout << y << endl;


	}
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(x_pred, y_pred);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(x, y);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2d(x, y);
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