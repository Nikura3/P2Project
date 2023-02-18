#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

class cube : public shape {

	private:
		point _center;
		double _edge;

	public:
		cube(const point& = point(), double = 0, double = 0, double = 0, double = 0);

		point getCenter() const;
		double getLength() const;
		std::vector<double> normal(const point&) const;
		std::tuple<bool, point> intersect(const point&, const std::vector<double>&) const;
		double lightning(const point&, const std::vector<double>&) const = 0;
		cube* clone() const = 0;
};

#endif
