
#include "Entities.h"

#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<Windows.h>


using namespace std;
using namespace cv; 


class Game
{
public:
	int resolutionHeigth;
	int resolutionWidth;


	double score;

	void initialize();
	void showWelcomeScreen();
	void chooseCharacter();
	void initializeMap();
	void runMap();
	
	string pauseGame();


	string windowName;
	Mat map;
	Entities entity[50];

	int mapSpeed;
	int mapPosition;
	int mapMilestone;


private:

	int charPosX = 500;
	int charPosY = 100;

	string windowName;
	Mat src;

	void configRead();
	void characterChangePosition();


};


