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
	void setResolution();
	void setResolution(int,int);
	void setWindowName(string);
	void makeWindow();
	void showWelcome();

private:
	 
	int resolutionHeigth;
	int resolutionWidth;
	string windowName;

};

