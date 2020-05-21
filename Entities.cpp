#include "Game.h"

#include<iostream>
#include<string>
#include <windows.h>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

Point mask[1][5];

Entities::Entities()
{
	identifier = "block";
	positionX = 0;
	positionY = 0;
	progress = 0;
	exists = false;
}

Entities::Entities(int id)
{
	identifier = id;
	positionX = 0;
	positionY = 0;
	progress = 0;
	exists = false;
}

void Entities::spawnEntity() 
{
	identifier = "block";
	positionX = rand() % 800 + 100;
	positionY = -50;
	exists = true;
	progress = 0;
	cout << "\nREPORT: stworzono istotê.";
}

void Entities::spawnEntity(string id)
{
	identifier = id;
	positionX = rand() % 800 + 100;
	positionY = -50;
	exists = true;
	progress = 0;
	cout << "\nREPORT: stworzono istotê.";
}

void Entities::drawSelf()
{
	cout << "\nERROR: próbowano narysowaæ istotê na niczym.";
}

void Entities::drawSelf(Mat map)
{
	if (identifier == "block") {
		rectangle(map, Point(positionX - 50, positionY + progress - 60), Point(positionX + 50, positionY + progress), Scalar(200, 200, 200), FILLED);
		rectangle(map, Point(positionX - 50, positionY + progress - 60), Point(positionX + 50, positionY + progress-40), Scalar(150, 150, 150), FILLED);
		rectangle(map, Point(positionX - 50, positionY + progress - 60), Point(positionX + 50, positionY + progress), Scalar(50, 50, 50), 2);
		rectangle(map, Point(positionX - 50, positionY + progress - 60), Point(positionX + 50, positionY + progress - 40), Scalar(50, 50, 50), 1);
	}
	if (identifier == "koronawirus") {
		circle(map, Point(positionX, positionY + progress), 25, Scalar(0, 0, 255), FILLED);
		line(map, Point(positionX + 10, positionY + progress + 10), Point(positionX + 20, positionY + progress + 30), Scalar(0, 0, 150), 2);
		circle(map, Point(positionX + 20, positionY + progress + 30), 3, Scalar(0, 0, 200));
		line(map, Point(positionX - 10, positionY + progress -20), Point(positionX - 30, positionY + progress -30), Scalar(0, 0, 150), 2);
		circle(map, Point(positionX - 30, positionY + progress - 30), 3, Scalar(0, 0, 200));
		line(map, Point(positionX - 10, positionY + progress), Point(positionX - 25, positionY + progress + 5), Scalar(0, 0, 150), 2);
		circle(map, Point(positionX - 25, positionY + progress + 5), 3, Scalar(0, 0, 200));
		line(map, Point(positionX + 10, positionY + progress - 10), Point(positionX + 30, positionY + progress - 20), Scalar(0, 0, 150), 2);
		circle(map, Point(positionX + 30, positionY + progress - 20), 3, Scalar(0, 0, 200));
	}
	if (identifier == "accel") {
		line(map, Point(positionX - 20, positionY + progress), Point(positionX, positionY + progress - 30), Scalar(0, 255, 255), 1.5);
		line(map, Point(positionX + 20, positionY + progress), Point(positionX, positionY + progress - 30), Scalar(0, 255, 255), 1.5);
		line(map, Point(positionX - 20, positionY + progress -10), Point(positionX, positionY + progress - 40), Scalar(0, 180, 255), 2);
		line(map, Point(positionX + 20, positionY + progress -10), Point(positionX, positionY + progress - 40), Scalar(0, 180, 255), 2);
		line(map, Point(positionX - 20, positionY + progress - 20), Point(positionX, positionY + progress - 50), Scalar(0, 140, 255), 3);
		line(map, Point(positionX + 20, positionY + progress - 20), Point(positionX, positionY + progress - 50), Scalar(0, 140, 255), 3);
	}
	if (identifier == "brake") {
		line(map, Point(positionX - 20, positionY + progress -40), Point(positionX, positionY + progress - 30), Scalar(0, 50, 255), 2);
		line(map, Point(positionX + 20, positionY + progress -40), Point(positionX, positionY + progress - 30), Scalar(0, 50, 255), 2);
		line(map, Point(positionX - 20, positionY + progress -50), Point(positionX, positionY + progress - 40), Scalar(0, 100, 255), 2);
		line(map, Point(positionX + 20, positionY + progress -50), Point(positionX, positionY + progress - 40), Scalar(0, 100, 255), 2);
		line(map, Point(positionX - 20, positionY + progress -60), Point(positionX, positionY + progress - 50), Scalar(0, 150, 255), 3);
		line(map, Point(positionX + 20, positionY + progress -60), Point(positionX, positionY + progress - 50), Scalar(0, 150, 255), 3);
	}
	if (identifier == "pill") {
		rectangle(map, Point(positionX - 20, positionY + progress), Point(positionX, positionY + progress - 10), Scalar(255, 255, 255), FILLED);
		rectangle(map, Point(positionX + 20, positionY + progress), Point(positionX, positionY + progress - 10), Scalar(255, 100, 100), FILLED);
		circle(map, Point(positionX - 20, positionY + progress - 5), 5, Scalar(255, 255, 255), FILLED);
		circle(map, Point(positionX + 20, positionY + progress - 5), 5, Scalar(255, 100, 100), FILLED);
	}
	if (identifier == "mask") {
		mask[0][0] = Point(positionX - 20, positionY + progress - 30);
		mask[0][1] = Point(positionX + 20, positionY + progress - 30);
		mask[0][2] = Point(positionX + 20, positionY + progress);
		mask[0][3] = Point(positionX, positionY + progress + 10);
		mask[0][4] = Point(positionX - 20, positionY + progress);

		const Point* ppt[1] = { mask[0] };
		int npt[] = { 5 };

		fillPoly(map, ppt, npt, 1, Scalar(255, 0, 0));
		line(map, Point(positionX, positionY + progress - 20), Point(positionX, positionY + progress - 5), Scalar(255, 255, 255), 2);
		line(map, Point(positionX -10, positionY + progress - 12), Point(positionX + 10, positionY + progress - 12), Scalar(255, 255, 255), 2);
	}
}
