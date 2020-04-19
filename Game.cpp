#include "Game.h"
#include "Character.h"


#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include <windows.h>
#include<filesystem>
#include <time.h>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;



void Game::initialize()   //Initialization of main game window.
{
        configRead(); //Setting up and reading window configuration from text file.
}

void Game::configRead()
{
    string line;
    windowName = "Koronaferie";

    ifstream configReader("Config.txt"); //Opening of Config.txt to get initialize info from it.
    if (configReader.is_open())
    {

        getline(configReader, line, '\n'); //Getting resolution height from Config.txt and converting it into integer.
        getline(configReader, line, '\n');
        stringstream height(line);
        height >> resolutionHeigth;
        cout << "DEBUG INFO: Ustawiona w pliku Config.txt wysokosc okna wynosi:" << resolutionHeigth << "px" << endl;

        getline(configReader, line, '\n'); //Getting resolution width from Config.txt and converting it into integer.
        getline(configReader, line, '\n');
        stringstream width(line);
        width >> resolutionWidth;
        cout << "DEBUG INFO: Ustawiona w pliku Config.txt szerokosc okna wynosi:" << resolutionWidth << "px" << endl;
        cout << "DEBUG INFO: Poprawnie odczytano rozdzielczość okna z pliku" << endl;
    }
    else
    {
        cout << "DEBUG INFO: Cos poszlo nie tak z otwarciem pliku Config.txt" << endl;
    }
    configReader.close(); //Closing Config.txt file
}

void Game::showWelcomeScreen() {

    cout << "DEBUG INFO: Zaczynam wyswietlac animacje" << endl;
    while (true) //Image animation loop
    {

        for (int frameCounter = 1; frameCounter <= 6; frameCounter++) {

            imshow(windowName, imread("menu" + to_string(frameCounter) + ".jpg", CV_LOAD_IMAGE_COLOR));
            if (cvWaitKey(50) == 13) //if ENTER is pressed, kill animation loop.
            {
                cout << "DEBUG INFO: Wcisnieto ENTER, przechodze do wyboru postaci" << endl;
                return;
            }

        }
        
    }
        
}

void Game::chooseCharacter() {

    int rectMoveX = 0;
    int chosenCharacter = 3;
    Mat CharacterMenu = Mat(resolutionHeigth, resolutionWidth, CV_16U); //Creating Mat Matrix of resolution set in Config.txt
    CharacterMenu = imread("charactermenu.jpg", CV_LOAD_IMAGE_COLOR); //Loads basic character menu background
    rectangle(CharacterMenu, Point(395 + rectMoveX, 400), Point(555 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
    imshow(windowName, CharacterMenu);
    cout << "DEBUG INFO: Poprawnie zaladowano ekran wyb. post." << endl;


    while (true) {
        
        int pressedKey = cvWaitKey(1);

        //if (pressedKey != -1) //-------------------------------->KEYCODECHECKER
        //{
        //    cout << to_string(pressedKey) << endl; 
        //}

        if ((pressedKey == 2555904) && (chosenCharacter != 5)) //right arrow 
        {
            rectMoveX += 180;
            chosenCharacter += 1;
            cout << "rightarrow postac: " << to_string(chosenCharacter) << endl;

            CharacterMenu = imread("charactermenu.jpg", CV_LOAD_IMAGE_COLOR);
            rectangle(CharacterMenu, Point(390 + rectMoveX, 400), Point(560 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
            imshow(windowName, CharacterMenu);
        }

        if ((pressedKey == 2424832) && (chosenCharacter != 1)) //left arrow 
        {
            rectMoveX -= 180;
            chosenCharacter--;
            cout << "leftarrow postac: " << to_string(chosenCharacter) << endl;

            CharacterMenu = imread("charactermenu.jpg", CV_LOAD_IMAGE_COLOR);
            rectangle(CharacterMenu, Point(390 + rectMoveX, 400), Point(560 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
            imshow(windowName, CharacterMenu);
        }

        if (pressedKey == 13) //if ENTER is pressed
        {
            CharacterMenu = imread("charactermenu.jpg", CV_LOAD_IMAGE_COLOR);
            rectangle(CharacterMenu, Point(300,300), Point(700,700), Scalar(255, 255, 255), CV_FILLED, 0);
            rectangle(CharacterMenu, Point(300, 300), Point(700, 700), Scalar(0, 0, 0), 1, 0);
            putText(CharacterMenu, "Wpisz nazwe postaci:", Point(320, 400), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1, 8, false);
            imshow(windowName, CharacterMenu);

            std::string currentCharacterName;
            pressedKey = 0;
            srand(time(NULL));

            while (true) {

                pressedKey = waitKey(500);
                //randR = rand() % 255 - 10;
                //randG = rand() % 255 - 10;
                //randB = rand() % 255 - 10;

     
                    if ((pressedKey != -1) && (pressedKey != 13))
                    {
                        if ((pressedKey == 8) && (currentCharacterName.length() != 0))
                        {
                            currentCharacterName.pop_back();
                            cout << "DEBUG INFO: Aktualna nazwa postaci: " << currentCharacterName << endl;
                        }
                        else if (currentCharacterName.length() < 20)
                        {
                            currentCharacterName.push_back((char)pressedKey);
                            cout << "DEBUG INFO: Aktualna nazwa postaci: " << currentCharacterName << endl;
                        }

                        rectangle(CharacterMenu, Point(300, 300), Point(700, 700), Scalar(255, 255, 255), CV_FILLED, 0);
                        putText(CharacterMenu, currentCharacterName, Point(320, 500), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 0, 0), 1, 8, false);
                    }

                    if (pressedKey == 13) {
                        Character Player;
                        Player.characterName = currentCharacterName;
                        cout << "Wybrano postac: " << chosenCharacter << ",jej nazwa to: " << Player.characterName;
                        return;
                    }
                    rectangle(CharacterMenu, Point(300, 300), Point(700, 700), Scalar((rand() % 255) - 10, (rand() % 255) - 10, (rand() % 255) - 10), 4, 0);
                    putText(CharacterMenu, "Wpisz nazwe postaci:", Point(320, 400), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 1, 8, false);
                    putText(CharacterMenu, "Jesli skonczyles edytowanie nazwy postaci kliknij ENTER", Point(305, 680), FONT_HERSHEY_COMPLEX, 0.4, Scalar(0, 0, 0), 1, 8, false);
                    imshow(windowName, CharacterMenu);
            }
            waitKey(0);
        }
        
    }
}

