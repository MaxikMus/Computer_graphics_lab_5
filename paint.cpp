#include "paint.h"

void Brezenkhem(POINT from, POINT to, HDC hdc, COLORREF color) {
	int signX = (to.x >= from.x ? 1 : -1);
	int signY = (to.y >= from.y ? 1 : -1);

	int lengthX = abs(to.x - from.x);
	int lengthY = abs(to.y - from.y);

	int length = max(lengthX, lengthY);

	if (length == 0) {
		SetPixel(hdc, from.x, from.y, color);
		return;
	}

	if (lengthY <= lengthX) {

		int x = from.x;
		int y = from.y;
		int d = -lengthX;

		length++;
		while (length--) {
			SetPixel(hdc, x, y, color);
			x += signX;
			d += 2 * lengthY;
			if (d > 0) {
				d -= 2 * lengthX;
				y += signY;
			}
		}
	}
	else {

		int x = from.x;
		int y = from.y;
		int d = -lengthY;

		length++;
		while (length--) {
			SetPixel(hdc, x, y, color);
			y += signY;
			d += 2 * lengthX;
			if (d > 0) {
				d -= 2 * lengthY;
				x += signX;
			}
		}
	}
}