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

	void initialize();
	void showWelcomeScreen();
	void chooseCharacter();
	void initializeMap();
	void runMap();
	string pauseGame();


private:


	int mapSpeed;
	int mapPosition;
	int mapMilestone;
	string windowName;
	Mat src;
	Mat map;

	void configRead();

};


