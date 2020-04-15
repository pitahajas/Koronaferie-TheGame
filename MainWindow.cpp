#include "MainWindow.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include <windows.h>
#include<filesystem>

using namespace std;
using namespace cv;



void MainWindow::initialize()   //Initialization of main game window.
{
        configRead(); //Setting up and reading window configuration from text file.
}

void MainWindow::configRead()
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
    }
    else
    {
        cout << "DEBUG INFO: Cos poszlo nie tak z otwarciem pliku Config.txt" << endl;
    }
    configReader.close(); //Closing Config.txt file
}

void MainWindow::showWelcomeScreen() {

    while (true) //Image animation loop
    {

        for (int frameCounter = 1; frameCounter <= 6; frameCounter++) {

            imshow(windowName, imread("menu" + to_string(frameCounter) + ".jpg", CV_LOAD_IMAGE_COLOR));
            if (cvWaitKey(50) == 13) //if ENTER is pressed, kill animation loop.
            {
                return;
            }

        }
        
    }
        
}

void MainWindow::chooseCharacter() {

    int rectMoveX = 0;
    int choosedCharacter = 3;
    Mat CharacterMenu = Mat(resolutionHeigth, resolutionWidth, CV_16U); //Creating Mat Matrix of resolution set in Config.txt
    CharacterMenu = imread("charactermenu.jpg", CV_LOAD_IMAGE_COLOR); //Loads basic character menu background
    rectangle(CharacterMenu, Point(395 + rectMoveX, 400), Point(555 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
    imshow(windowName, CharacterMenu);

    while (true) {
        
        int pressedKey = cvWaitKey(1);

        //if (pressedKey != -1) //-------------------------------->KEYCODECHECKER
        //{
        //    cout << to_string(pressedKey) << endl; 
        //}

        if ((pressedKey == 2555904) && (choosedCharacter != 5)) //right arrow 
        {
            rectMoveX += 180;
            choosedCharacter += 1;
            cout << "rightarrow postac: " << to_string(choosedCharacter) << endl;

            CharacterMenu = imread("charactermenu.jpg", CV_LOAD_IMAGE_COLOR);
            rectangle(CharacterMenu, Point(390 + rectMoveX, 400), Point(560 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
            imshow(windowName, CharacterMenu);
        }

        if ((pressedKey == 2424832) && (choosedCharacter != 1)) //left arrow 
        {
            rectMoveX -= 180;
            choosedCharacter--;
            cout << "leftarrow postac: " << to_string(choosedCharacter) << endl;

            CharacterMenu = imread("charactermenu.jpg", CV_LOAD_IMAGE_COLOR);
            rectangle(CharacterMenu, Point(390 + rectMoveX, 400), Point(560 + rectMoveX, 580), Scalar(0, 240, 255), 3, 8);
            imshow(windowName, CharacterMenu);
        }

        if (pressedKey == 13) //if ENTER is pressed
        {
            return;
        }
        
    }
}

