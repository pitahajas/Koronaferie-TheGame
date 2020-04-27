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

private:

	int resolutionHeigth;
	int resolutionWidth;
	string windowName;

	void configRead();

};

