#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;
using namespace cv;

class Character
{
public:

	string characterName;
	int characterSkin;
	int posX;
	int posY;

	void draw();
	void draw(Mat mapinput, int posX, int posY);

private:


};