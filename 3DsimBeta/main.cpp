#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "windows.h"
#include "base_functions.h"
#include "aux_functions.h"

using namespace std;

int main() {

	//ask for number of shapes to render and other parameters, just so I don't have to change the code everytime I want something different
	cout << "Display timer? 0 for no, 1 for yes." << endl;
	cin >> showtimer;
	cout << "How many shapes do you want to render?" << endl;
	cin >> NumOfShapesToRender;
	if (NumOfShapesToRender == -1) {
		NumOfShapesToRender = 0;
		GraphFunction(0, 0, 200);
	}
	else if (NumOfShapesToRender == -2) {
		runl = 1;
		NumOfShapesToRender = 0;
	}
	else{
		for (int i = 0; i < NumOfShapesToRender; i++) {
			//adjust order to have correct number of places
			order.push_back(0);
			//ask for type of each shape
			cout << "Type of shape " << i + 1 << "?" << endl;
			cout << "0 for point" << endl << "1 for line" << endl << "2 for surface" << endl;
			cin >> TypeTemp;
			//record class of shape in type
			type.push_back(TypeTemp);
			//ask for coordinates based on case, and adjust each vector to have the correct length
			if (TypeTemp == 0) {
				cout << "input x, y, and z" << endl;
				for (int j = 0; j < 3; j++) {
					cin >> CoordinateTemp[j];
				}
				p1.push_back(CoordinateTemp);
				p2.push_back({ 0,0,0 });
				p3.push_back({ 0,0,0 });
			}
			else if (TypeTemp == 1) {
				cout << "input x1, y1, z1, x2, y2, and z2" << endl;
				for (int j = 0; j < 3; j++) {
					cin >> CoordinateTemp[j];
				}
				p1.push_back(CoordinateTemp);
				for (int j = 0; j < 3; j++) {
					cin >> CoordinateTemp[j];
				}
				p2.push_back(CoordinateTemp);
				p3.push_back({ 0,0,0 });
			}
			else {
				cout << "input x1, y1, z1, x2, y2, z2, x3, y3, and z3" << endl;
				for (int j = 0; j < 3; j++) {
					cin >> CoordinateTemp[j];
				}
				p1.push_back(CoordinateTemp);
				for (int j = 0; j < 3; j++) {
					cin >> CoordinateTemp[j];
				}
				p2.push_back(CoordinateTemp);
				for (int j = 0; j < 3; j++) {
					cin >> CoordinateTemp[j];
				}
				p3.push_back(CoordinateTemp);
			}
			s1.push_back({ 0,0,0 });
			s2.push_back({ 0,0,0 });
			s3.push_back({ 0,0,0 });
			//ask for color, make sure it works 
			cout << "What color? Input in RGB values" << endl;
			for (int j = 0; j < 3; j++) {
				cin >> CoordinateTemp[j];
			}
			coloruuuuuuu.push_back(CoordinateTemp);
		}
	}

	while (window.isOpen()) {
		//record start time
		t = clock();
		counter++;

		//clear window and get mousepos
		window.clear();
		mousePos = sf::Mouse::getPosition(window);

		//check for closing window
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		//receive input from keyboard
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) {
				yes[1] = -scale;
			}
			if (event.key.code == sf::Keyboard::Down) {
				yes[1] = scale;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
				scale += 0.01;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
				scale -= 0.01;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				yes[0] = -scale;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				yes[0] = scale;
			}
		}
		else {
			for (int i = 0; i < yes.size(); i++) {
				yes[i] = 0;
			}
		}

		//recieve input from mouse 
		//lol tbh idk how to write instructions on using this, just move ur mouse around and it'll make sense after like a few minutes
		if (abs(mousePos.x - WinSize / 2) > 200) {
			yr += rotationspeed * (signbit((float)(mousePos.x - WinSize / 2)) * 2 - 1);
		}
		if (abs(mousePos.y - WinSize / 2) > 200) {
			xr += rotationspeed * (signbit((float)(mousePos.y - WinSize / 2)) * 2 - 1);
			zr += -rotationspeed * (signbit((float)(mousePos.y - WinSize / 2)) * 2 - 1);
		}

		//-------------------------
		
		//run various dynamic systems
		RunSim();

		//rotate the shapes
		for (int i = 0; i < type.size(); i++) {
			if (type[i] == 0) {
				s1[i] = rotation(p1[i][0], p1[i][1], p1[i][2], xr, 0);
				s1[i] = rotation(s1[i][0], s1[i][1], s1[i][2], yr, 1);
				s1[i] = rotation(s1[i][0], s1[i][1], s1[i][2], zr, 2);
			}
			else if (type[i] == 1) {
				s1[i] = rotation(p1[i][0], p1[i][1], p1[i][2], xr, 0);
				s1[i] = rotation(s1[i][0], s1[i][1], s1[i][2], yr, 1);
				s1[i] = rotation(s1[i][0], s1[i][1], s1[i][2], zr, 2);

				s2[i] = rotation(p2[i][0], p2[i][1], p2[i][2], xr, 0);
				s2[i] = rotation(s2[i][0], s2[i][1], s2[i][2], yr, 1);
				s2[i] = rotation(s2[i][0], s2[i][1], s2[i][2], zr, 2);
			}
			else {
				s1[i] = rotation(p1[i][0], p1[i][1], p1[i][2], xr, 0);
				s1[i] = rotation(s1[i][0], s1[i][1], s1[i][2], yr, 1);
				s1[i] = rotation(s1[i][0], s1[i][1], s1[i][2], zr, 2);

				s2[i] = rotation(p2[i][0], p2[i][1], p2[i][2], xr, 0);
				s2[i] = rotation(s2[i][0], s2[i][1], s2[i][2], yr, 1);
				s2[i] = rotation(s2[i][0], s2[i][1], s2[i][2], zr, 2);

				s3[i] = rotation(p3[i][0], p3[i][1], p3[i][2], xr, 0);
				s3[i] = rotation(s3[i][0], s3[i][1], s3[i][2], yr, 1);
				s3[i] = rotation(s3[i][0], s3[i][1], s3[i][2], zr, 2);
			}
		}

		//translate each shape
		for (int i = 0; i < type.size(); i++) {
			if (type[i] == 0) {
				p1[i][0] += yes[0];
				p1[i][1] += yes[1];
				p1[i][2] += yes[2];
			}
			else if (type[i] == 1) {
				p1[i][0] += yes[0];
				p1[i][1] += yes[1];
				p1[i][2] += yes[2];

				p2[i][0] += yes[0];
				p2[i][1] += yes[1];
				p2[i][2] += yes[2];
			}
			else {
				p1[i][0] += yes[0];
				p1[i][1] += yes[1];
				p1[i][2] += yes[2];

				p2[i][0] += yes[0];
				p2[i][1] += yes[1];
				p2[i][2] += yes[2];

				p3[i][0] += yes[0];
				p3[i][1] += yes[1];
				p3[i][2] += yes[2];
			}
		}

		//order each shape
		organize();

		//render, color, and shade each shape
		for (int i = 0; i < type.size(); i++) {
			if (type[order[i]] == 0) {
				//treat the point as a circle of rad=5, set and draw it
				boll.setPosition(s1[order[i]][0] * scale + CenterOfScreen, s1[order[i]][1] * scale + CenterOfScreen);
				boll.setFillColor(sf::Color(coloruuuuuuu[order[i]][0], coloruuuuuuu[order[i]][1], coloruuuuuuu[order[i]][2]));
				window.draw(boll);
			}
			else if (type[order[i]] == 1) {
				//set line
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(s1[order[i]][0] * scale + CenterOfScreen, s1[order[i]][1] * scale + CenterOfScreen), sf::Color(coloruuuuuuu[order[i]][0], coloruuuuuuu[order[i]][1], coloruuuuuuu[order[i]][2])),
					sf::Vertex(sf::Vector2f(s2[order[i]][0] * scale + CenterOfScreen, s2[order[i]][1] * scale + CenterOfScreen), sf::Color(coloruuuuuuu[order[i]][0], coloruuuuuuu[order[i]][1], coloruuuuuuu[order[i]][2]))
				};
				//draw line
				window.draw(line, 2, sf::Lines);
			}
			else {
				// resize it to 3 points
				kaiser.setPointCount(3);

				// define the points
				kaiser.setPoint(0, sf::Vector2f(s1[order[i]][0] * scale + CenterOfScreen, s1[order[i]][1] * scale + CenterOfScreen));
				kaiser.setPoint(1, sf::Vector2f(s2[order[i]][0] * scale + CenterOfScreen, s2[order[i]][1] * scale + CenterOfScreen));
				kaiser.setPoint(2, sf::Vector2f(s3[order[i]][0] * scale + CenterOfScreen, s3[order[i]][1] * scale + CenterOfScreen));

				//set color with shading
				shad = shading(s1[order[i]][0], s1[order[i]][1], s1[order[i]][2], s2[order[i]][0], s2[order[i]][1], s2[order[i]][2], s3[order[i]][0], s3[order[i]][1], s3[order[i]][2]);
				kaiser.setFillColor(sf::Color(shad * coloruuuuuuu[order[i]][0] + 25, shad * coloruuuuuuu[order[i]][1] + 25, shad * coloruuuuuuu[order[i]][2] + 25));

				window.draw(kaiser);
			}
		}

		//-------------------------

		//display 
		window.display();

		//record end time
		t = clock() - t;
		if (showtimer) {
			cout << "time elapsed: " << ((float)t) / CLOCKS_PER_SEC << endl;
		}
	}
	
	return 0;
}
