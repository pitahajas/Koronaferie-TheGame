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

private:

	int resolutionHeigth = 0;
	int resolutionWidth = 0;
	string windowName;

	void configRead();

};

