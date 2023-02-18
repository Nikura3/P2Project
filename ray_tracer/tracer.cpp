#include <iostream>
#include <tuple>
#include "tracer.h"
#include "math_utilities.h"

void tracer(std::ostream& os, unsigned int res) {

	long double x = 0;
	long double y = 0;
	long double ldres = static_cast<long double>(res);
	std::vector<double> color(3);

	os << "P3 " << res * 100 << " " << res * 100 << " " << MAX_COLOR_VALUE << std::endl;

	for (y = -50; y <= 50-1./ldres; y += 1./ldres) {
		for (x = -50; x <= 50-1./ldres; x += 1./ldres) {
			color = colorAt(x, y);
			os << color[0] << " " << color[1] << " " << color[2] << std::endl;
		}
	}
}

const std::vector<double> colorAt(double x, double y) {

	std::vector<double> ray(3);

	ray[0] = x - eye.getX();
	ray[1] = y - eye.getY();
	ray[2] = 0 - eye.getZ();

	vecNormalize(ray);
	sendRay(eye, ray);
	vecScalarMultiply(ray, MAX_COLOR_VALUE);
	vecRound(ray);

	return ray;
}

void sendRay(const point& eye, std::vector<double>& ray) {

	std::tuple<shape*, point> shape_hit = shapeHit(eye, ray);
	shape* s = std::get<0>(shape_hit);
	point p = std::get<1>(shape_hit);

	double intensity;

	if (s != nullptr) {
		intensity = s->lightning(p, ray);
		ray[0] = intensity * s->getColorX();
		ray[1] = intensity * s->getColorY();
		ray[2] = intensity * s->getColorZ();
	} else {
		ray = backgroun_color;
	}
}

std::tuple<shape*, point> shapeHit(const point& eye, const std::vector<double>& ray) {

	std::tuple<bool, point> intersection;
	std::tuple<shape*, point> shape_hit;
	double min_distance = 0;
	double d;

	shape_hit = std::make_tuple(nullptr, point());

	list<shape*>::const_iterator cit;
	for (cit = global_world.begin(); cit != global_world.end(); ++cit) {
		intersection = (*cit)->intersect(eye, ray);

		if (std::get<0>(intersection)) {
			d = eye.distance(std::get<1>(intersection));
			if (min_distance == 0 || d < min_distance) {
				min_distance = d;
				shape_hit = std::make_tuple(*cit, std::get<1>(intersection));
			}
		}
	}

	return shape_hit;
}
