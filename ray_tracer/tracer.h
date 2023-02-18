#ifndef TRACER_H
#define TRACER_H

#include <vector>
#include "shape.h"
#include "list.h"

#define MAX_COLOR_VALUE 255
const std::vector<double> backgroun_color = {0, 0, 0};
const point eye(0, 0, 200);
extern list<shape*> global_world;

void tracer(std::ostream& os, unsigned int res = 1);
const std::vector<double> colorAt(double x, double y);
void sendRay(const point&, std::vector<double>&);
std::tuple<shape*, point> shapeHit(const point&, const std::vector<double>&);
double lambert(shape*, const point&, const std::vector<double>&);

#endif
