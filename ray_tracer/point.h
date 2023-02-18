#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>

class point {

	private:
		std::vector<double> _coordinates;

	public:
		point(double = 0, double = 0, double = 0);
		operator std::vector<double>() const;
		double getX() const;
		double getY() const;
		double getZ() const;
		double distance(const point&) const;
};

std::ostream& operator<<(std::ostream&, const point&);

#endif
