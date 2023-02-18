#include <cmath>
#include "math_utilities.h"

double vecMagnitude(const std::vector<double>& v) {
	double mag = 0;

	for (std::vector<double>::const_iterator it = v.begin(); it != v.end(); ++it) {
		mag += *it * *it;
	}

	return sqrt(mag);
}

double vecDifference(const std::vector<double>& v1, const std::vector<double>& v2) {

	std::vector<double> difference;

	std::vector<double>::const_iterator it1 = v1.begin();
	std::vector<double>::const_iterator it2 = v2.begin();
	while (it1 != v1.end() && it2 != v2.end()) {
		difference.push_back(*it1 - *it2);
		++it1;
		++it2;
	}

	return vecMagnitude(difference);
}

void vecNormalize(std::vector<double>& v) {
	double mag = vecMagnitude(v);

	for (std::vector<double>::iterator it = v.begin(); it != v.end(); ++it) {
		*it /= mag;
	}
}

void vecScalarMultiply(std::vector<double>& v, double k) {
	for (std::vector<double>::iterator it = v.begin(); it != v.end(); ++it) {
		*it *= k;
	}
}

void vecRound(std::vector<double>& v) {
	for (std::vector<double>::iterator it = v.begin(); it != v.end(); ++it) {
		*it = round(*it);
	}
}

double vecDotProduct(const std::vector<double>& v1, const std::vector<double>& v2) {

	double dot_product = 0;

	std::vector<double>::const_iterator it1 = v1.begin();
	std::vector<double>::const_iterator it2 = v2.begin();
	while (it1 != v1.end() && it2 != v2.end()) {
		dot_product += *it1 * *it2;
		++it1;
		++it2;
	}

	return dot_product;
}

//finds minimum root for ax^2 + bx + c = 0
std::tuple<bool, double> minroot(double a, double b, double c) {

	std::tuple<bool, double> partial = partialMinroot(a, b, c);

	if (a == 0 && b == 0 && c == 0) {
		return std::make_tuple(true, 0);	//tautology: there is no minimum
	} else if (a == 0 && b == 0 && c != 0) {
		return std::make_tuple(false, double());  	//there are no solutions
	} else if (a == 0) {
		return std::make_tuple(true, -(c/b));	 //b is not zero or one of the conditions above would have been satisfied: first grade equation
	} else if (std::get<0>(partial) == false) {
		return std::make_tuple(false, double());	//solution is complex
	} else {
		return std::make_tuple(true, min( ((-b + sqrt(std::get<1>(partial))) / 2*a), ((-b - sqrt(std::get<1>(partial))) / 2*a)));	//any other case
	}
}

std::tuple<bool, double> partialMinroot(double a, double b, double c) {
	if ( (b*b - 4*a*c) < 0) {
		return std::make_tuple(false, double());
	} else {
		return std::make_tuple(true, b*b - 4*a*c);
	}
}

// solves |a + xb| = c, assuming b > 0, c > 0
std::tuple<bool, std::vector<double>> solveModule(double a, double b, double c) {

	std::vector<double> x(2);

	x[0] = (c - a) / b;
	x[1] = (-c - a) / b;

	return std::make_tuple(true, x);
}

double min(double a, double b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

double min(double a, double b, double c) {
	if (a < b) {
		if (a < c) {
			return a;
		} else {
			return c;
		}
	} else {
		if (b < c) {
			return b;
		} else {
			return c;
		}
	}
}

double max(double a, double b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}
double max(double a, double b, double c) {
	if (a > b) {
		if (a > c) {
			return a;
		} else {
			return c;
		}
	} else {
		if (b > c) {
			return b;
		} else {
			return c;
		}
	}
}
