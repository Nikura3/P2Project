#include "toon_cube.h"
#include "math_utilities.h"

tcube::tcube(const point& center, double radius, double r, double g, double b, unsigned int intervals) : cube(center, radius, r, g, b), _intervals(intervals) {}

double tcube::lightning(const point& p, const std::vector<double>& ray) const {

	std::vector<double> n = normal(p);

	double intensity = vecDotProduct(ray, n);
	double intervals = static_cast<double>(_intervals);

	for (unsigned int i = 0; i < _intervals; ++i) {
		if (i/intervals < intensity && intensity < (i+1)/intervals) {
			intensity = i/intervals + ( 1 / (intervals*2));
		}
	}

	return max(intensity, 0);
}

tcube* tcube::clone() const {
	return new tcube(*this);
}
