#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "math_utilities.h"
#include "node.h"
#include "list.h"
#include "tracer.h"
#include "realistic_sphere.h"
#include "toon_sphere.h"
#include "realistic_cube.h"
#include "toon_cube.h"

list<shape*> global_world;
std::string getwd();

void readInput(std::string, unsigned int*);
std::string getwd();

int main() {

	std::string wd = getwd();
	std::string input_file = wd + "ray_tracer/input";
	std::string output_file = wd + "ray_tracer/image.ppm";
	std::ofstream ofile;
	ofile.open(output_file, std::ofstream::out | std::ofstream::trunc);

	unsigned int res;

	readInput(input_file, &res);

	tracer(ofile, res);

	ofile.close();

	return 0;
}

void readInput(std::string in, unsigned int* res) {

	char object, light;
	double x, y, z, rad, r, g, b, i;

	std::ifstream ifile(in, std::ifstream::in);

	ifile >> *res;

	while ((ifile >> object) && !ifile.eof()) {
		ifile >> light;
		ifile >> x;
		ifile >> y;
		ifile >> z;
		ifile >> rad;
		ifile >> r;
		ifile >> g;
		ifile >> b;
		if (object == 'S') {
			if (light == 'R') {
				global_world.append(new rsphere(point(x, y, z), rad, r, g, b));
			} else {
				ifile >> i;
				global_world.append(new tsphere(point(x, y, z), rad, r, g, b, i));
			}
		} else if (object == 'C') {
			if (light == 'R') {
				global_world.append(new rcube(point(x, y, z), rad, r, g, b));
			} else {
				ifile >> i;
				global_world.append(new tcube(point(x, y, z), rad, r, g, b, i));
			}
		}
	}
	ifile.close();
}

std::string getwd() {

	char wd[FILENAME_MAX];
	std::string d;

	if (getcwd(wd, sizeof(wd))) {
		d = static_cast<std::string>(wd);
		d.pop_back();
		d.pop_back();
		d.pop_back();
		return d;
	} else {
		return "";
	}
}
