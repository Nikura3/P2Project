#ifndef REALISTIC_CUBE_H
#define REALISTIC_CUBE_H

#include "cube.h"

class rcube : public cube {

	public:
		rcube(const point& = point(), double = 0, double = 0, double = 0, double = 0);

		double lightning(const point&, const std::vector<double>&) const;
		rcube* clone() const;
};

#endif
