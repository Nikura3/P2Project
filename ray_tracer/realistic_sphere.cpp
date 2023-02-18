#include "realistic_sphere.h"
#include "math_utilities.h"

rsphere::rsphere(const point& center, double radius, double r, double g, double b) : sphere(center, radius, r, g, b) {}

double rsphere::lightning(const point& p, const std::vector<double>& ray) const {

	std::vector<double> n = normal(p);

	double intensity = vecDotProduct(ray, n);

	return max(intensity, 0);
}

rsphere* rsphere::clone() const {
	return new rsphere(*this);
}
