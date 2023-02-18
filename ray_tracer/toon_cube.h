#ifndef TOON_CUBE_H
#define TOON_CUBE_H

#include "cube.h"

class tcube : public cube {

	private:
		unsigned int _intervals;

	public:
		tcube(const point& = point(), double = 0, double = 0, double = 0, double = 0, unsigned int = 10);

		double lightning(const point&, const std::vector<double>&) const;
		tcube* clone() const;
};

#endif
