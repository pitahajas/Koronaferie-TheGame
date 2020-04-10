#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<Windows.h>


using namespace std;
using namespace cv; 


class MakeWindow
{
public:
	int resolutionHeigth;
	int resolutionWidth;
	string windowName;
	
	void setResolution();
	void setResolution(int,int);
	void setWindowName(string);
	void makeWindow();
	void showWelcome();

private:
	 


};

