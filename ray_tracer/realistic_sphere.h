#ifndef REALISTIC_SPHERE_H
#define REALISTIC_SPHERE_H

#include "sphere.h"

class rsphere : public sphere {

	public:
		rsphere(const point& = point(), double = 0, double = 0, double = 0, double = 0);

		double lightning(const point&, const std::vector<double>&) const;
		rsphere* clone() const;
};

#endif
