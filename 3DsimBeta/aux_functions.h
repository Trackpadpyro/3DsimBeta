#pragma once

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include "base_functions.h"

using namespace std;

//premade function: run code = -1
float fun(float x, float y) {
	x = x / 100;
	y = y / 100;
	return sin(x + y) * 100;
}
//for graphing stuff, this generates the points and puts them in the vectors
void GraphFunction(float red, float blue, float green) {
	for (float i = -resolution; i < resolution; i++) {
		for (float j = -resolution; j < resolution; j++) {
			type.push_back(2);
			order.push_back(0);
			CoordinateTemp = { red, blue, green };
			coloruuuuuuu.push_back(CoordinateTemp);
			CoordinateTemp = { i * gridsize / resolution, j * gridsize / resolution, fun(i * gridsize / resolution, j * gridsize / resolution) };
			p1.push_back(CoordinateTemp);
			CoordinateTemp = { (i + 1) * gridsize / resolution, j * gridsize / resolution, fun((i + 1) * gridsize / resolution, j * gridsize / resolution) };
			p2.push_back(CoordinateTemp);
			CoordinateTemp = { i * gridsize / resolution, (j + 1) * gridsize / resolution, fun(i * gridsize / resolution, (j + 1) * gridsize / resolution) };
			p3.push_back(CoordinateTemp);

			s1.push_back({ 0,0,0 });
			s2.push_back({ 0,0,0 });
			s3.push_back({ 0,0,0 });

			type.push_back(2);
			order.push_back(0);
			CoordinateTemp = { red, blue, green };
			coloruuuuuuu.push_back(CoordinateTemp);
			CoordinateTemp = { (i + 1) * gridsize / resolution, (j + 1) * gridsize / resolution, fun((i + 1) * gridsize / resolution, (j + 1) * gridsize / resolution) };
			p1.push_back(CoordinateTemp);
			CoordinateTemp = { (i + 1) * gridsize / resolution, j * gridsize / resolution, fun((i + 1) * gridsize / resolution, j * gridsize / resolution) };
			p2.push_back(CoordinateTemp);
			CoordinateTemp = { i * gridsize / resolution, (j + 1) * gridsize / resolution, fun(i * gridsize / resolution, (j + 1) * gridsize / resolution) };
			p3.push_back(CoordinateTemp);

			s1.push_back({ 0,0,0 });
			s2.push_back({ 0,0,0 });
			s3.push_back({ 0,0,0 });
		}
	}
}

//dynamical system: run code = -2
//chaos system coordinates, trail size is how far it trails, runl is whether or not to run it, stepsize is how large differentials are
//param1/2/3 and x/y/zderiv dictate the parameters and differential equation derivatives
int trailsize = 100;
bool runl = 0;
float stepsize = 0.001;
float xin = 10;
float yin = 50;
float zin = 10;
float param1 = 100;
float xderiv() {
	return param1 * (yin - xin);
}
float param2 = 280;
float yderiv() {
	return (xin * (param2 - zin) - yin);
}
float param3 = 80 / 3;
float zderiv() {
	return (xin * yin - param3 * zin);
}
void RunSim() {
	if (runl && counter < trailsize) {
		order.push_back(0);

		type.push_back(1);

		p1.push_back({ xin,yin,zin });

		p2.push_back({ xin + stepsize * xderiv(), yin + stepsize * yderiv(), zin + stepsize * zderiv() });

		p3.push_back({ 0,0,0 });

		s1.push_back({ 0,0,0 });
		s2.push_back({ 0,0,0 });
		s3.push_back({ 0,0,0 });

		coloruuuuuuu.push_back({ 200,200,200 });

		xin = p2[p2.size() - 1][0];
		yin = p2[p2.size() - 1][1];
		zin = p2[p2.size() - 1][2];

	}
	if (runl && counter >= trailsize) {
		p1[NumOfShapesToRender + 3 + ((int)counter % (trailsize - 1))] = { xin,yin,zin };

		p2[NumOfShapesToRender + 3 + ((int)counter % (trailsize - 1))] = { xin + stepsize * xderiv(), yin + stepsize * yderiv(), zin + stepsize * zderiv() };

		xin = p2[NumOfShapesToRender + 3 + ((int)counter % (trailsize - 1))][0];
		yin = p2[NumOfShapesToRender + 3 + ((int)counter % (trailsize - 1))][1];
		zin = p2[NumOfShapesToRender + 3 + ((int)counter % (trailsize - 1))][2];

	}

}
