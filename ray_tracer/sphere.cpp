#include "sphere.h"
#include "math_utilities.h"

sphere::sphere(const point& center, double radius, double r, double g, double b) : shape(r, g, b), _center(center), _radius(max(0, radius)) {}

point sphere::getCenter() const {
	return _center;
}

double sphere::getRadius() const {
	return _radius;
}

std::vector<double> sphere::normal(const point& p) const {

	std::vector<double> normal(3);

	normal[0] = _center.getX() - p.getX();
	normal[1] = _center.getY() - p.getY();
	normal[2] = _center.getZ() - p.getZ();

	vecNormalize(normal);

	return normal;
}

std::tuple<bool, point> sphere::intersect(const point& eye, const std::vector<double>& ray) const {

	double a, b, c;
	double x0_xc, y0_yc, z0_zc;;

	x0_xc = eye.getX() - _center.getX();
	y0_yc = eye.getY() - _center.getY();
	z0_zc = eye.getZ() - _center.getZ();

	a = ray[0]*ray[0] + ray[1]*ray[1] + ray[2]*ray[2];

	b = 2 * ((x0_xc * ray[0]) + (y0_yc * ray[1]) + (z0_zc * ray[2]));

	c = x0_xc*x0_xc + y0_yc*y0_yc + z0_zc*z0_zc - _radius*_radius;

	std::tuple<bool, double> root = minroot(a, b, c);

	if (std::get<0>(root) == false) {
		return std::make_tuple(false, point());
	} else {
		point intersection(eye.getX() + std::get<1>(root)*ray[0], eye.getY() + std::get<1>(root)*ray[1], eye.getZ() + std::get<1>(root)*ray[2]);
		return std::make_tuple(true, intersection);
	}
}
