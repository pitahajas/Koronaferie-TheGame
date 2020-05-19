﻿#include "Game.h"
#include "Character.h"
#include "CharacterChoiceWindow.h"


#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include <windows.h>
#include<filesystem>
#include <time.h>
#include<opencv2\opencv.hpp>

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

            imshow(windowName, imread("menu" + to_string(frameCounter) + ".jpg", IMREAD_COLOR));
            if (waitKey(50) == 13) //if ENTER is pressed, kill animation loop.
            {
                cout << "DEBUG INFO: Wcisnieto ENTER, przechodze do wyboru postaci" << endl;
                return;
            }

        }
        
    }
        
}

void Game::chooseCharacter() {

    CharacterChoiceWindow ChoiceWindow;
    ChoiceWindow.initialize(resolutionHeigth, resolutionWidth, windowName);

    while (true) {

        int pressedKey = waitKey(1);

        if ((pressedKey == 100) && (ChoiceWindow.chosenCharacter != 5)) //right arrow 
        {
            ChoiceWindow.moveRectangle("right");
            ChoiceWindow.rectangleUpdate(windowName);
        }

        if ((pressedKey == 97) && (ChoiceWindow.chosenCharacter != 1)) //left arrow 
        {
            ChoiceWindow.moveRectangle("left");
            ChoiceWindow.rectangleUpdate(windowName);
        }

        if (pressedKey == 13) //if ENTER is pressed
        {
            ChoiceWindow.textboxInitialize(windowName);
            ChoiceWindow.textboxUpdate(windowName);

            Character Player;
            Player.characterName = ChoiceWindow.chosenCharacterName;
            cout << "Wybrano postac: " << ChoiceWindow.chosenCharacter << ", jej nazwa to: " << Player.characterName;
            return;
        }
    }
}

void Game::initializeMap()
{
    src = Mat(11000, 1000, CV_32FC3); //Creating a Mat matrix for the full map
    src = imread("Map.jpg", IMREAD_COLOR); //Storing the full map
    map = src(Range(10000, 11000), Range(0, 1000)); //Extracting Initial Region of Interest for the window and storing it in the matrix
    imshow(windowName, map);
    cout << "\nZaladowano mape.";
    mapSpeed = 6;  
    mapPosition = 0;
    mapMilestone = 0; 
    score = 0;
    //^ Initial variable values, used in Game::runMap()
    waitKey();
}

void Game::runMap()
{
    map = src(Range(10000 - mapPosition, 11000 - mapPosition), Range(0, 1000));
    imshow(windowName, map);
    mapPosition += mapSpeed;
    if(mapPosition >=10000)
        mapPosition -= 10000;
    cout << "\nPozycja mapy: " << mapPosition;
    score += (double)mapSpeed/100;
    cout << "\nWYNIK: " << (int)score;
    mapMilestone += mapSpeed; //Tracking milestones every 1000 pixels for speed incrementation.
    if (mapMilestone >= 1000)
    {
        mapSpeed += 1;
        mapMilestone -= 1000;
        cout << "\nMAP SPEED +1 = " << mapSpeed;
    }
    Sleep(10);
}

string Game::pauseGame()
{
    map = imread("Menu_pauzy.jpg", IMREAD_COLOR);
    imshow(windowName, map);
    char input;
    while (true)
    {
        input = waitKey();
        if (input == 27)
            return "Escape";
        else if (input == 32)
            return "Space";
    }
}