#include "Game.h"

#include<iostream>
#include<string>
#include <windows.h>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;


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
	if(identifier=="block")
		circle(map, Point(positionX, positionY + progress), 25, Scalar(64, 64, 64), FILLED);
	if (identifier == "koronawirus")
		circle(map, Point(positionX, positionY + progress), 25, Scalar(0, 0, 255), FILLED);
	if (identifier == "accel")
		circle(map, Point(positionX, positionY + progress), 25, Scalar(0, 255, 255), FILLED);
	if (identifier == "brake")
		circle(map, Point(positionX, positionY + progress), 25, Scalar(0, 128, 255), FILLED);
	if (identifier == "pill")
		circle(map, Point(positionX, positionY + progress), 25, Scalar(255, 128, 0), FILLED);
	if (identifier == "mask")
		circle(map, Point(positionX, positionY + progress), 25, Scalar(255, 255, 255), FILLED);
}
