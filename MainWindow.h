#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<Windows.h>


using namespace std;
using namespace cv; 


class MainWindow
{
public:
	
	void Initialize();
	void ShowWelcomeScreen();

private:

	int resolutionHeigth = 0;
	int resolutionWidth = 0;
	string windowName;

	void ConfigRead();

};

