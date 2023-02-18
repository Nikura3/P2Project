#include "realistic_cube.h"
#include "math_utilities.h"

rcube::rcube(const point& center, double radius, double r, double g, double b) : cube(center, radius, r, g, b) {}

double rcube::lightning(const point& p, const std::vector<double>& ray) const {

	std::vector<double> n = normal(p);

	double intensity = vecDotProduct(ray, n);

	return max(intensity, 0);
}

rcube* rcube::clone() const {
	return new rcube(*this);
}
