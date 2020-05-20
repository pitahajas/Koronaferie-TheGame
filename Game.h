#include "Character.h"
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
	int mapSpeed;
	int mapPosition;
	int mapMilestone;
	int pressedKey;

	double score;
	double highScore;

	void initialize();
	void showWelcomeScreen();
	void chooseCharacter();
	void initializeGame();
	void runMap();
	void checkCollisions();
	void checkCollisions(int i);

	string endGame();
	string pauseGame();

	string windowName;
	Mat map;
	Entities entity[50];
	Character Player;



private:

	Mat src;

	void configRead();

};


