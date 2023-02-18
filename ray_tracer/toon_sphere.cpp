#include "toon_sphere.h"
#include "math_utilities.h"

tsphere::tsphere(const point& center, double radius, double r, double g, double b, unsigned int intervals) : sphere(center, radius, r, g, b), _intervals(intervals) {}

double tsphere::lightning(const point& p, const std::vector<double>& ray) const {

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

tsphere* tsphere::clone() const {
	return new tsphere(*this);
}
