#ifndef MATH_UTILITIES
#define MATH_UTILITIES

#include <tuple>
#include <vector>

double vecMagnitude(const std::vector<double>&);
double vecDifference(const std::vector<double>&, const std::vector<double>&);
void vecNormalize(std::vector<double>&);
void vecScalarMultiply(std::vector<double>& v, double k);
void vecRound(std::vector<double>& v);
double vecDotProduct(const std::vector<double>& v1, const std::vector<double>& v2);
std::tuple<bool, double> minroot(double a, double b, double c);
std::tuple<bool, double> partialMinroot(double a, double b, double c);
std::tuple<bool, std::vector<double>> solveModule(double a, double b, double c);
double min(double, double);
double min(double, double, double);
double max(double, double);
double max(double, double, double );

#endif
