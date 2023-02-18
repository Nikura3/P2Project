#include "cube.h"
#include "math_utilities.h"

cube::cube(const point& center, double edge, double r, double g, double b) : shape(r, g, b), _center(center), _edge(max(0, edge)) {}

point cube::getCenter() const {
	return _center;
}

double cube::getLength() const {
	return _edge;
}

std::vector<double> cube::normal(const point& p) const {

	std::vector<double> normal(3);

	if (p.getX() == _center.getX() + _edge/2) {
		normal[0] = -1;
		normal[1] = 0;
		normal[2] = 0;
	} else if (p.getX() == _center.getX() - _edge/2) {
		normal[0] = 1;
		normal[1] = 0;
		normal[2] = 0;
	} else if (p.getY() == _center.getY() + _edge/2) {
		normal[0] = 0;
		normal[1] = -1;
		normal[2] = 0;
	} else if (p.getY() == _center.getY() - _edge/2) {
		normal[0] = 0;
		normal[1] = 1;
		normal[2] = 0;
	} else if (p.getZ() == _center.getZ() + _edge/2) {
		normal[0] = 0;
		normal[1] = 0;
		normal[2] = -1;
	} else if (p.getZ() == _center.getZ() - _edge/2) {
		normal[0] = 0;
		normal[1] = 0;
		normal[2] = 1;
	}

	return normal;
}

std::tuple<bool, point> cube::intersect(const point& eye, const std::vector<double>& ray) const {

	double x0_xc, y0_yc, z0_zc;
	std::tuple<bool, std::vector<double>> solX, solY, solZ;
	std::vector<double> vecLambda;
	double x, y, z;
	std::vector<point> possible_intersections;
	point intersection;
	double min_distance;
	unsigned int i;

	x0_xc = eye.getX() - _center.getX();
	y0_yc = eye.getY() - _center.getY();
	z0_zc = eye.getZ() - _center.getZ();

	solX = solveModule(x0_xc, ray[0], _edge/2);
	solY = solveModule(y0_yc, ray[1], _edge/2);
	solZ = solveModule(z0_zc, ray[2], _edge/2);

	if (std::get<0>(solX)) {
		vecLambda.push_back((std::get<1>(solX))[0]);
		vecLambda.push_back((std::get<1>(solX))[1]);
	}

	if (std::get<0>(solY)) {
		vecLambda.push_back((std::get<1>(solY))[0]);
		vecLambda.push_back((std::get<1>(solY))[1]);
	}

	if (std::get<0>(solZ)) {
		vecLambda.push_back((std::get<1>(solZ))[0]);
		vecLambda.push_back((std::get<1>(solZ))[1]);
	}

	for (i = 0; i < vecLambda.size(); ++i) {
		x = eye.getX() + vecLambda[i]*ray[0];
		y = eye.getY() + vecLambda[i]*ray[1];
		z = eye.getZ() + vecLambda[i]*ray[2];
		if (max(std::abs(x - _center.getX()), std::abs(y - _center.getY()), std::abs(z - _center.getZ())) == _edge/2) {
			possible_intersections.push_back(point(x, y, z));
		}
	}

	if (possible_intersections.size() > 0) {

		intersection = possible_intersections[0];
		min_distance = eye.distance(intersection);

		for (i = 1; i < possible_intersections.size(); ++i) {
			if (eye.distance(possible_intersections[i]) < min_distance) {
				intersection = possible_intersections[i];
				min_distance = eye.distance(intersection);
			}
		}

		return std::make_tuple(true, intersection);

	} else {

		return std::make_tuple(false, point());
	}
}
