#include "shape.h"
#include "math_utilities.h"

point::point (double x, double y, double z) {
	_coordinates.push_back(x);
	_coordinates.push_back(y);
	_coordinates.push_back(z);
}

point::operator std::vector<double>() const {
	std::vector<double> aux = {_coordinates[0], _coordinates[1], _coordinates[2]};
	return aux;
}

double point::getX() const {
	return _coordinates[0];
}

double point::getY() const {
	return _coordinates[1];
}

double point::getZ() const {
	return _coordinates[2];
}

double point::distance(const point& p) const {
	return vecDifference(*this, p);
}

std::ostream& operator<<(std::ostream& os, const point& p) {
  return os << '(' << p.getX() << ',' << p.getY() << ','
	    << p.getZ() << ')';
}
