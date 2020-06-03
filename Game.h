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

	int pressedKey;

	double highScore;

	void initialize();
	void showWelcomeScreen();
	void chooseCharacter();

	void initializeGame();
	void runGame();

	string endGame();
	string pauseGame();

	bool isPlayerDead();

private:

	Mat src;
	Mat map;
	Entities entity[50];
	Character Player;

	string windowName;
	string highScoreHolder;
	
	double score;
	int resolutionHeigth;
	int resolutionWidth;
	int mapMilestone;
	int mapPosition;
	int mapSpeed;

	void configRead();

	void initializeVariables();
	void showTutorial(Mat map);

	void drawScoreBox(Mat map, double score);
	void updateVariables();
	void readInput(int pressedKey);

};
