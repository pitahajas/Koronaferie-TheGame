#ifndef __wtypes_h__
#include <wtypes.h>
#endif

#ifndef __WINDEF_
#include <windef.h>
#endif

#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>

using namespace std;
using namespace cv;

class CharacterChoiceWindow
{
public:

	void initialize();
	void initialize(int resHeigth, int resWidth, string windowName);

	void moveRectangle();
	void moveRectangle(string windowName);

	void rectangleUpdate();
	void rectangleUpdate(string windowName);

	void textboxInitialize();
	void textboxInitialize(string windowName);

	void textboxUpdate();
	void textboxUpdate(string windowName);

	int chosenCharacter = 3;
	string chosenCharacterName;

	Mat CharacterMenu;


private:



	int rectMoveX = 0;
	int pressedKey = 0;


};