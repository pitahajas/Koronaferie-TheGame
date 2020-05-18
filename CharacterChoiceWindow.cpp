#include "CharacterChoiceWindow.h"
#include "Game.h"

#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>

void CharacterChoiceWindow::initialize() {
	cout << "Nie wprowadzono zadnych argumentow, potrzebnych metodzie initialize(resHeigth, resWidth, windowName)";
}

void CharacterChoiceWindow::moveRectangle() {
	cout << "Nie podano, w ktora strone ma sie poruszyc ramka";
}

void CharacterChoiceWindow::rectangleUpdate() {}
void CharacterChoiceWindow::textboxInitialize(){}
void CharacterChoiceWindow::textboxUpdate() {}

//------------------------------------------------------------------------------------------------------------------------

void CharacterChoiceWindow::initialize(int resolutionHeigth, int resolutionWidth, string windowName) {
	CharacterMenu = Mat(resolutionHeigth, resolutionWidth, CV_16U); //Creating Mat Matrix of resolution set in Config.txt
	CharacterMenu = imread("charactermenu.jpg", IMREAD_COLOR); //Loads basic character menu background
	rectangle(CharacterMenu, Point(395 + rectMoveX, 400), Point(555 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
	imshow(windowName, CharacterMenu);
	cout << "DEBUG INFO: Poprawnie zaladowano ekran wyb. post." << endl;
}

void CharacterChoiceWindow::moveRectangle(string direction) {

	if (direction == "right") {
		rectMoveX += 180;
		chosenCharacter += 1;
		cout << "rightarrow postac: " << to_string(chosenCharacter) << endl;
	}
	else {
		if (direction == "left") {
			rectMoveX -= 180;
			chosenCharacter--;
			cout << "leftarrow postac: " << to_string(chosenCharacter) << endl;
		}
		else 
		cout << "wprowadzono bledny argument metody moveRectangle";
	}

}

void CharacterChoiceWindow::rectangleUpdate(string windowName) {
	CharacterMenu = imread("charactermenu.jpg", IMREAD_COLOR);
	rectangle(CharacterMenu, Point(390 + rectMoveX, 400), Point(560 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
	imshow(windowName, CharacterMenu);
}

void CharacterChoiceWindow::textboxInitialize(string windowName) {

	CharacterMenu = imread("charactermenu.jpg", IMREAD_COLOR);
	rectangle(CharacterMenu, Point(300, 300), Point(700, 700), Scalar(255, 255, 255), FILLED, 0);
	rectangle(CharacterMenu, Point(300, 300), Point(700, 700), Scalar(0, 0, 0), 1, 0);
	putText(CharacterMenu, "Wpisz nazwe postaci:", Point(320, 400), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 1, 8, false);
	imshow(windowName, CharacterMenu);
	srand(time(NULL));

}

void CharacterChoiceWindow::textboxUpdate(string windowName) {

	while (true) {

		pressedKey = waitKey(500);

		if ((pressedKey != -1) && (pressedKey != 13))
		{
			if ((pressedKey == 8) && (chosenCharacterName.length() != 0))
			{
				chosenCharacterName.pop_back();
				cout << "DEBUG INFO: Aktualna nazwa postaci: " << chosenCharacterName << endl;
			}
			else if (chosenCharacterName.length() < 20)
			{
				chosenCharacterName.push_back((char)pressedKey);
				cout << "DEBUG INFO: Aktualna nazwa postaci: " << chosenCharacterName << endl;
			}

			rectangle(CharacterMenu, Point(300, 300), Point(700, 700), Scalar(255, 255, 255), FILLED, 0);
			putText(CharacterMenu, chosenCharacterName, Point(320, 500), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 0, 0), 1, 8, false);
		}

		if (pressedKey == 13) {
			return;
		}
		rectangle(CharacterMenu, Point(300, 300), Point(700, 700), Scalar((rand() % 255) - 10, (rand() % 255) - 10, (rand() % 255) - 10), 4, 0);
		putText(CharacterMenu, "Wpisz nazwe postaci:", Point(320, 400), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 1, 8, false);
		putText(CharacterMenu, "Jesli skonczyles edytowanie nazwy postaci kliknij ENTER", Point(305, 680), FONT_HERSHEY_COMPLEX, 0.4, Scalar(0, 0, 0), 1, 8, false);
		imshow(windowName, CharacterMenu);
	}
	waitKey(0);
}




