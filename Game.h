#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<Windows.h>


using namespace std;
using namespace cv; 


class Game
{
public:
	
	void initialize();
	void showWelcomeScreen();
	void chooseCharacter();
	void initializeMap();
	void runMap();

private:

	int resolutionHeigth;
	int resolutionWidth;
	int mapSpeed;
	int mapPosition;
	int mapMilestone;
	string windowName;
	Mat src;
	Mat map;

	void configRead();

};

