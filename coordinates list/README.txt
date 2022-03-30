This project has a couple specifications in order to work. 

If one does not need to actually edit the code, then there is an .exe file in x64 > Debug that will work, even if SFMl isn't installed. Otherwise, the program expects SFML to be in "C:/SFML-2.5.1". For practical purposes, the variables: "gridsize", "WinSize", "resolution", "rotationspeed", and "scale", should be adjusted as needed in order to fit the computer. 

The program will prompt you for an input as soon as it starts it recognizes one of three basic shapes: points, lines, and triangular surfaces. The origin is defined as the center of the screen initially, color is defined from 0 to 199 on a RGB scale. Although, one may choose to simply enter their own shapes composed of surfaces, but there are several other options. The program recognizes the code "-1" which graphs the pre existing function coded as "fun" in "Shapes.h", I'm using this to test for efficiency. The folder "coordinates list" contains text files that provide premade instructions to the program to render stuff. The following is a list of descriptions:

1. a regular tetrahedron 
2. a regular icosahedron

The program starts with the coordinate axis "rendered", x is red, y is green, and z is blue. But it really just draws lines of length "gridsize" along the axis, and you start by viewing the system from beneath the xy plane with the positive x axis pointing right and the positive y axis pointing down. Rotations still rotate along the invisible but present x, y, and z axis and the origin and translations will move all points in the direction you specify. So Controlling the program is kind of bad, since I defined rotations and translations in a way that's counterintuitive to the human mind. 

I really don't know how to make instructions for this, just know that your mouse commands the rotations, and it makes sense once you get used to it. Translations are done with the arrow keys and PgUp and PgDown, because apparently SFML has trouble detecting other keys on my keyboard. 

The program counts how fast each frame takes to render on average and outputs it into the command line, this is to calculate efficiency and speed.