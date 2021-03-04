#include "Coordinate.h"

Coordinate::Coordinate(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Coordinate::Coordinate() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}