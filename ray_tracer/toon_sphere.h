#ifndef TOON_SPHERE_H
#define TOON_SPHERE_H

#include "sphere.h"

class tsphere : public sphere {

	private:
		unsigned int _intervals;

	public:
		tsphere(const point& = point(), double = 0, double = 0, double = 0, double = 0, unsigned int = 10);

		double lightning(const point&, const std::vector<double>&) const;
		tsphere* clone() const;
};

#endif
