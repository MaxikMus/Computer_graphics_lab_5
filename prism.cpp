#include "prism.h"

Prism::Prism() {
	for (size_t i = 0; i < 16; i++)
	{
		isV[i] = true;
	}
	_z = 100;
	p = new POINT[10];
	figure = new point[10];
	_refresh = new point[10];
	_polygon = new int* [16];
	for (size_t i = 0; i < 16; i++) {
		_polygon[i] = new int[3];
	}
	for (size_t i = 0, j = 400; i < 2; i++, j += 200) {
		(figure + 0 + i * 5)->x = 200;
		(figure + 0 + i * 5)->y = 400;
		(figure + 0 + i * 5)->z = j;

		(figure + 1 + i * 5)->x = 295;
		(figure + 1 + i * 5)->y = 331;
		(figure + 1 + i * 5)->z = j;

		(figure + 2 + i * 5)->x = 259;
		(figure + 2 + i * 5)->y = 219;
		(figure + 2 + i * 5)->z = j;

		(figure + 3 + i * 5)->x = 141;
		(figure + 3 + i * 5)->y = 219;
		(figure + 3 + i * 5)->z = j;

		(figure + 4 + i * 5)->x = 105;
		(figure + 4 + i * 5)->y = 331;
		(figure + 4 + i * 5)->z = j;
	}

	{
		_polygon[0][0] = 0;
		_polygon[0][1] = 4;
		_polygon[0][2] = 3;

		_polygon[1][0] = 0;
		_polygon[1][1] = 3;
		_polygon[1][2] = 2;

		_polygon[2][0] = 0;
		_polygon[2][1] = 2;
		_polygon[2][2] = 1;
		//
		_polygon[3][0] = 5;
		_polygon[3][1] = 9;
		_polygon[3][2] = 8;

		_polygon[4][0] = 5;
		_polygon[4][1] = 8;
		_polygon[4][2] = 7;

		_polygon[5][0] = 5;
		_polygon[5][1] = 7;
		_polygon[5][2] = 6;
		//
		_polygon[6][0] = 0;
		_polygon[6][1] = 5;
		_polygon[6][2] = 1;

		_polygon[7][0] = 1;
		_polygon[7][1] = 6;
		_polygon[7][2] = 5;
		//
		_polygon[8][0] = 1;
		_polygon[8][1] = 2;
		_polygon[8][2] = 6;

		_polygon[9][0] = 7;
		_polygon[9][1] = 2;
		_polygon[9][2] = 6;
		//
		_polygon[10][0] = 3;
		_polygon[10][1] = 2;
		_polygon[10][2] = 7;

		_polygon[11][0] = 3;
		_polygon[11][1] = 8;
		_polygon[11][2] = 7;
		//
		_polygon[12][0] = 4;
		_polygon[12][1] = 3;
		_polygon[12][2] = 8;

		_polygon[13][0] = 4;
		_polygon[13][1] = 9;
		_polygon[13][2] = 8;
		//
		_polygon[14][0] = 4;
		_polygon[14][1] = 9;
		_polygon[14][2] = 0;

		_polygon[15][0] = 0;
		_polygon[15][1] = 5;
		_polygon[15][2] = 9;
		//
	}
	
	for (size_t i = 0; i < 10; i++) {
		_refresh[i] = figure[i];
	}

}

Prism ::~Prism() {
	delete[] figure;
	delete[] _refresh;
	for (size_t i = 0; i < 16; i++)	{
		delete[] _polygon[i];
	}
	delete[] _polygon;
	delete[] p;
}

void Prism::sortP(point user) {
	double l, r;
	for (int i = 0; i < 16; i++) {
		bool flag = true;
		for (int j = 0; j < 16 - (i + 1); j++) {
			point temp;
			temp.x = (figure[_polygon[j][0]].x + figure[_polygon[j][1]].x + figure[_polygon[j][2]].x) / 3;
			temp.y = (figure[_polygon[j][0]].y + figure[_polygon[j][1]].y + figure[_polygon[j][2]].y) / 3;
			temp.z = (figure[_polygon[j][0]].z + figure[_polygon[j][1]].z + figure[_polygon[j][2]].z) / 3;
			l = sqrt(pow(0 - temp.x, 2) + pow(0 - temp.y, 2) + pow(_z - temp.z, 2));

			temp.x = (figure[_polygon[j + 1][0]].x + figure[_polygon[j + 1][1]].x + figure[_polygon[j + 1][2]].x) / 3;
			temp.y = (figure[_polygon[j + 1][0]].y + figure[_polygon[j + 1][1]].y + figure[_polygon[j + 1][2]].y) / 3;
			temp.z = (figure[_polygon[j + 1][0]].z + figure[_polygon[j + 1][1]].z + figure[_polygon[j + 1][2]].z) / 3;
			r = sqrt(pow(0 - temp.x, 2) + pow(0 - temp.y, 2) + pow(_z - temp.z, 2));


			if (l < r) {
				flag = false;
				auto temp = _polygon[j];
				_polygon[j] = _polygon[j + 1];
				_polygon[j + 1] = temp;
			}
		}
		if (flag) 
			break;
	}
}

void Prism::showPrism(HDC hdc, long Width, long Height) {




	point center;
	center.x = Width / 2;
	center.y = Height / 2;
	sortP(center);

	for (size_t i = 0; i < 16; i++) {
		for (size_t j = 0; j < 3; j++) {
			p[_polygon[i][j]].x = static_cast<long>((_z * (figure + _polygon[i][j])->x) / (figure + _polygon[i][j])->z) + center.x;
			p[_polygon[i][j]].y = static_cast<long>((_z * (figure + _polygon[i][j])->y) / (figure + _polygon[i][j])->z) + center.y;
		}
	}
	shade(hdc);

}


void Prism::shade(HDC hdc) {
	POINT from, to;
	for (size_t i = 0; i < 16; i++) {
		long x = 0;
		long x1 = 0;

		if (p[_polygon[i][0]].y > p[_polygon[i][1]].y) std::swap(_polygon[i][0], _polygon[i][1]);
		if (p[_polygon[i][1]].y > p[_polygon[i][2]].y) std::swap(_polygon[i][1], _polygon[i][2]);
		if (p[_polygon[i][0]].y > p[_polygon[i][1]].y) std::swap(_polygon[i][0], _polygon[i][1]);

		unsigned int first = _polygon[i][0], last = _polygon[i][2], middle = _polygon[i][1];


		MoveToEx(hdc, p[first].x, p[first].y, 0);
		LineTo(hdc, p[last].x, p[last].y);

		//Brezenkhem(p[first], p[last], hdc, BLUE);

		for (long y = p[first].y; y < p[middle].y; y++) {
			if ((p[middle].y - p[first].y) == 0 || (p[last].y - p[first].y) == 0) {
				continue;
			}
			x = (((y - p[first].y) * (p[middle].x - p[first].x)) / (p[middle].y - p[first].y)) + p[first].x;
			x1 = (((y - p[first].y) * (p[last].x - p[first].x)) / (p[last].y - p[first].y)) + p[first].x;
			from.x = x;
			from.y = y;

			to.x = x1;
			to.y = y;


			MoveToEx(hdc, from.x, from.y, 0);
			LineTo(hdc, to.x, to.y);

			//Brezenkhem(from, to, hdc, BLUE);
		}

		for (long y = p[middle].y; y < p[last].y; y++) {
			if ((p[last].y - p[middle].y) == 0 || (p[last].y - p[first].y) == 0) {
				continue;
			}
			x = (((y - p[middle].y) * (p[last].x - p[middle].x)) / (p[last].y - p[middle].y)) + p[middle].x;
			x1 = (((y - p[first].y) * (p[last].x - p[first].x)) / (p[last].y - p[first].y)) + p[first].x;
			from.x = x;
			from.y = y;

			to.x = x1;
			to.y = y;

			MoveToEx(hdc, from.x, from.y, 0);
			LineTo(hdc, to.x, to.y);

			//Brezenkhem(from, to, hdc, BLUE);

		}
		

		for (size_t j = 0; j < 3; j++) {

			/*MoveToEx(hdc, p[_polygon[i][j]].x, p[_polygon[i][j]].y, 0);
			LineTo(hdc, p[_polygon[i][(j + 1) % 3]].x, p[_polygon[i][(j + 1) % 3]].y);*/

			Brezenkhem(p[_polygon[i][j]], p[_polygon[i][(j + 1) % 3]], hdc, BLUE);
		}
	}
}

void Prism::refresh() {
	for (size_t i = 0; i < 10; i++) {
		figure[i] = _refresh[i];
	}
}

void Prism::rotate(double angle, unsigned int axis) {
	double temp;

	point center;
	for (size_t i = 0; i < 10; i++) {
		center.x = center.x + (figure + i)->x;
		center.y = center.y + (figure + i)->y;
		center.z = center.z + (figure + i)->z;
	}
	center.x /= 10;
	center.y /= 10;
	center.z /= 10;

	switch (axis)
	{
	case X:
		for (size_t i = 0; i < 10; i++) {
			temp = (figure + i)->y;
			(figure + i)->y = ((figure + i)->y - center.y) * cos(angle) + ((figure + i)->z - center.z) * sin(angle) + center.y;
			(figure + i)->z = -(temp - center.y) * sin(angle) + ((figure + i)->z - center.z) * cos(angle) + center.z;

		}
		break;
	case Y:
		for (size_t i = 0; i < 10; i++) {
			temp = (figure + i)->x;
			(figure + i)->x = ((figure + i)->x - center.x) * cos(angle) + ((figure + i)->z - center.z) * sin(angle) + center.x;
			(figure + i)->z = -(temp - center.x) * sin(angle) + ((figure + i)->z - center.z) * cos(angle) + center.z;

		}

		break;
	case Z:
		for (size_t i = 0; i < 10; i++) {
			temp = (figure + i)->x;
			(figure + i)->x = ((figure + i)->x - center.x) * cos(angle) + ((figure + i)->y - center.y) * sin(angle) + center.x;
			(figure + i)->y = -(temp - center.x) * sin(angle) + ((figure + i)->y - center.y) * cos(angle) + center.y;

		}

		break;
	default:
		break;
	}
}

void Prism::scale(double scale) {

	point center;
	for (size_t i = 0; i < 10; i++) {
		center.x = center.x + (figure + i)->x;
		center.y = center.y + (figure + i)->y;
		center.z = center.z + (figure + i)->z;
	}
	center.x /= 10;
	center.y /= 10;
	center.z /= 10;

	scale = ((scale - 1) / 10) + 1;
	for (size_t i = 0; i < 10; i++) {
		(figure + i)->x = ((figure + i)->x - center.x) * scale + center.x;
		(figure + i)->y = ((figure + i)->y - center.y) * scale + center.y;
		(figure + i)->z = ((figure + i)->z - center.z) * scale + center.z;
	}
}

void Prism::move(double speed, unsigned int direction) {
	switch (direction)
	{
	case RIGHT:
		for (size_t i = 0; i < 10; i++) {
			(figure + i)->x += speed;
		}
		break;

	case LEFT:
		for (size_t i = 0; i < 10; i++) {
			(figure + i)->x -= speed;
		}

		break;

	case UP:
		for (size_t i = 0; i < 10; i++) {
			(figure + i)->y -= speed;
		}

		break;

	case DOWN:
		for (size_t i = 0; i < 10; i++) {
			(figure + i)->y += speed;
		}

		break;

	case FORWARD:
		for (size_t i = 0; i < 10; i++) {
			(figure + i)->z += speed;
		}

		break;
	case BACK:
	{
		bool exit = false;
		for (size_t i = 0; i < 10; i++) {
			if ((figure + i)->z <= 10)
				exit = true;
		}
		if (exit) break;
		for (size_t i = 0; i < 10; i++) {
			(figure + i)->z -= speed;
		}
	}


	break;
	default:
		break;
	}
}