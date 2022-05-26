#pragma once
#include <windows.h>
#include <cmath>
#include <iostream>
#include "paint.h"
#define RED RGB(255, 0, 0)
#define BLUE RGB(0, 0, 255)
#define BLACK RGB(0,0,0)
#define PI 3.14159265358979323846
#define gradToRad(x) x * PI/180 
enum AXIS
{
	Z,
	Y,
	X
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	BACK,
	FORWARD
};

struct point {
	double x, y, z;
	point() : x(0), y(0), z(0) {}
	point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	point(const point& copy) {
		this->x = copy.x;
		this->y = copy.y;
		this->z = copy.z;
	}
	void operator = (const point& copy) {
		this->x = copy.x;
		this->y = copy.y;
		this->z = copy.z;
	}
};

class Prism {
public:
	Prism();
	~Prism();

	void showPrism(HDC hdc, long Width, long Height);
	void move(double speed, unsigned int direction);
	void rotate(double angle, unsigned int axis);
	void scale(double scale);
	void refresh();

protected:
	void shade(HDC hdc);
	void sortP(point user);


private:
	double _z;
	point* figure;
	point* _refresh;
	POINT* p;
	bool isV[16];
	int** _polygon;
};