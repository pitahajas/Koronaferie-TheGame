#include "Character.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>

using namespace std;
using namespace cv;

void Character::draw() {}

Mat Character::draw(Mat mapinput, int posX, int posY) {


		Point czupryna[1][14];

		czupryna[0][0] = Point(posX, 1000 - posY + 70);
		czupryna[0][1] = Point(posX + 10, 1000 - posY + 20);
		czupryna[0][2] = Point(posX + 60, 1000 - posY + 20);
		czupryna[0][3] = Point(posX + 30, 1000 - posY);
		czupryna[0][4] = Point(posX + 60, 1000 - posY - 20);
		czupryna[0][5] = Point(posX + 25, 1000 - posY - 40);
		czupryna[0][6] = Point(posX + 35, 1000 - posY - 100);
		czupryna[0][7] = Point(posX, 1000 - posY - 70);
		czupryna[0][8] = Point(posX - 35, 1000 - posY - 100);
		czupryna[0][9] = Point(posX - 25, 1000 - posY - 40);
		czupryna[0][10] = Point(posX - 60, 1000 - posY - 20);
		czupryna[0][11] = Point(posX - 30, 1000 - posY);
		czupryna[0][12]= Point(posX - 60, 1000 - posY + 20);
		czupryna[0][13]= Point(posX - 10, 1000 - posY + 20);

		const Point* ppt[1] = { czupryna[0] };
		int npt[] = { 14 };

        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(255, 204, 204), FILLED);
		line(mapinput, Point(posX + 10, 950 - posY), Point(posX + 35, 950 - posY), Scalar(255, 0, 0), 2);
		line(mapinput, Point(posX - 10, 950 - posY), Point(posX - 35, 950 - posY), Scalar(255, 0, 0), 2);
		line(mapinput, Point(posX + 35, 950 - posY), Point(posX + 45, 1000 - posY), Scalar(255, 0, 0), 2);
		line(mapinput, Point(posX - 35, 950 - posY), Point(posX - 45, 1000 - posY), Scalar(255, 0, 0), 2);
		fillPoly(mapinput, ppt, npt, 1, Scalar(0, 255, 255),LINE_8);


    return mapinput;
}