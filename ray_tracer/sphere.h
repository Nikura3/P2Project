#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class sphere : public shape {

	private:
		point _center;
		double _radius;

	public:
		sphere(const point& = point(), double = 0, double = 0, double = 0, double = 0);

		point getCenter() const;
		double getRadius() const;
		std::vector<double> normal(const point&) const;
		std::tuple<bool, point> intersect(const point&, const std::vector<double>&) const;
		double lightning(const point&, const std::vector<double>&) const = 0;
		sphere* clone() const = 0;
};

#endif
