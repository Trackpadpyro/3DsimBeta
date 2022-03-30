#pragma once

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
#include <stdlib.h>

using namespace std;

int WinSize = 1000;

sf::RenderWindow window(sf::VideoMode(WinSize, WinSize), "main_window");

//excuse the names, my friends named them

//mouse position if I need it
sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//temp variables used for input, because C++ vectors get fussy when you directly input into them
bool showtimer;
int NumOfShapesToRender;
int TypeTemp;
vector<float> CoordinateTemp(3);
float counter;
//clock to time things
clock_t t;
float AvgT;

//grid sizes and other related variables, gridsize is the length of the axis, resolution is the length and width of each triangle which composes the graph
float gridsize = 300;
float resolution = 5;

//rotation storage, this determines the viewing angle and speed, different keyboards have different specifications for this, adjust as needed
float xr = 0.76;
float yr = -1.1;
float zr = -0.76;
float rotationspeed = 0.001;
//scale, because some screens are different, and window size is in px
float scale = 1;
//temp variable used for shading 
double shad;
//yes (R^3), for now it's set as 0 as I don't want things shifting
vector<int> yes{ 0, 0, 0 };

//first 3 entries in the vectors are for the coordinate axis 
//p1 is for point 1, p2 is for point 2, p3 is for point 3 (R^3)
vector<vector<float>> p1{ { 0, 0, 0 }, {0, 0, 0}, {0, 0, 0} };
vector<vector<float>> p2{ { gridsize, 0, 0 }, {0, gridsize, 0}, {0, 0, gridsize} };
vector<vector<float>> p3{ { 0, 0, 0 }, {0, 0, 0}, {0, 0, 0} };

vector<vector<float>> s1{ { 0, 0, 0 }, {0, 0, 0}, {0, 0, 0} };
vector<vector<float>> s2{ { 0, 0, 0 }, {0, 0, 0}, {0, 0, 0} };
vector<vector<float>> s3{ { 0, 0, 0 }, {0, 0, 0}, {0, 0, 0} };
//type (0/1/2) and represents the type of shape to render, 0 for point, 1 for line, 2 for surface
vector<int> type{ 1, 1, 1 };
//order (N), details the order in which to display things
vector<int> order{ 0, 1, 2 };
//coloruuuuuuu ([0, 200] x [0, 200] x [0, 200]) is the color of each shape in RGB
vector<vector<float>> coloruuuuuuu{ {200, 0, 0}, {0, 200, 0}, {0, 0, 200} };

//boll is used to render points, line is for lines, kaiser is my dog's name and its for surfaces
sf::CircleShape boll(5);
sf::Vertex line[];
sf::ConvexShape kaiser;

//Screen center, bc centering it at 0,0 is dumb
int CenterOfScreen = WinSize / 2;

//functions for calculating various numbers
//shading, currently using cross products
double shading(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	double area = sqrt(
		100 * pow(((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)), 2)
		/
		(100 * (
			pow(((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)), 2) +
			pow(((x2 - x1) * (z3 - z1) - (x3 - x1) * (z2 - z1)), 2) +
			pow(((z2 - z1) * (y3 - y1) - (z3 - z1) * (y2 - y1)), 2)
			))
	);
	return area;
}
//rotations, currently using rotation matrices
vector<float> rotation(float x, float y, float z, float angle, float axis) {
	//check for axis, then multiply by the corrosponding matrix, C++ has no matrix multiplication lib that works well, so I'll have to just hard code it
	vector<float> prime(3);
	if (axis == 0) {
		prime[0] = x;
		prime[1] = y * cos(angle) - z * sin(angle);
		prime[2] = z * cos(angle) + y * sin(angle);
	}
	else if (axis == 1) {
		prime[0] = x * cos(angle) - z * sin(angle);
		prime[1] = y;
		prime[2] = z * cos(angle) + x * sin(angle);
	}
	else {
		prime[0] = x * cos(angle) - y * sin(angle);
		prime[1] = y * cos(angle) + x * sin(angle);
		prime[2] = z;
	}
	return prime;
}
//translation
//there is no translation function, because it's just vector addition, so I just put it in main
//order
/*now that I think about it, this whole part is just bad spagetti code except the spagetti was cooked by Linguini from Ratatouille
none of it actually makes any sense, it relies upon the user defining the topology mesh using really 
small triangles or else the approximations break, and even still it's bound to be pretty slow. 
I should've just gone with a different algorithm, but meh I'll work on optimizing this last I guess. 
Theres an alternate organize function somewhere else in this folder but I don't really know which one is worse.*/
void organize() {
	vector<float> pos;
	float k, n;
	//calculate the position of each thing to render
	for (int i = 0; i < type.size(); i++) {
		if (type[i] == 0) {
			pos.push_back(s1[i][2]);
		}
		else if (type[i] == 1) {
			pos.push_back(( s1[i][2] + s2[i][2]) / 2);
		}
		else {
			pos.push_back(( s3[i][2] + s2[i][2] + s1[i][2] ) / 3);
		}
	}

	//find an serial number for each
	for (int i = 0; i < type.size(); i++) {
		n = pos[0];
		k = 0;
		//loop through pos, find the smallest, record it in order, set its position to MAXINT, repeat 
		for (int j = 0; j < pos.size(); j++) {
			if (n > pos[j]) {
				n = pos[j];
				k = j;
			}
		}
		order[i] = k;
		pos[k] =(float)MAXINT;
	}
}
//for non isometric display, scaling factor by distance depends on z value, -range to range will be scaled to 1 to 0.5
float range_of_display = 0;
float non_iso_scale(float z_value, float range ) {
	if (range == 0) {
		return (float)1;
	}
	else {
		return 2 * range / (3 * range + z_value);
	}
}
