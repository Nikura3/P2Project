#include "shape.h"
#include "math_utilities.h"

shape::shape(double r, double g, double b) {
	_color.push_back(r);
	_color.push_back(g);
	_color.push_back(b);
}

shape::~shape() {}

double shape::getColorX() const {
	return _color[0];
}

double shape::getColorY() const {
	return _color[1];
}

double shape::getColorZ() const {
	return _color[2];
}
