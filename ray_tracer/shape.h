#ifndef SHAPE_H
#define SHAPE_H

#include <tuple>
#include "point.h"

class shape {

	private:
		std::vector<double> _color;

	public:
		shape(double = 0, double = 0, double = 0);
		virtual ~shape();

		double getColorX() const;
		double getColorY() const;
		double getColorZ() const;
		virtual std::vector<double> normal(const point&) const = 0;
		virtual std::tuple<bool, point> intersect(const point&, const std::vector<double>&) const = 0;
		virtual double lightning(const point&, const std::vector<double>&) const = 0;
		virtual  shape* clone() const = 0;
};

#endif
