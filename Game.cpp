#include "Game.h"
#include "CharacterChoiceWindow.h"

#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include <windows.h>
#include <time.h>
#include<opencv2\opencv.hpp>
#include <conio.h>


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

            Player.characterName = ChoiceWindow.chosenCharacterName;
            cout << "Wybrano postac: " << ChoiceWindow.chosenCharacter << ", jej nazwa to: " << Player.characterName;
            return;
        }
    }
}

void Game::initializeGame()
{
    src = Mat(11000, 1000, CV_32FC3); //Creating a Mat matrix for the full map
    src = imread("Map.jpg", IMREAD_COLOR); //Storing the full map
    src(Range(10000, 11000), Range(0, 1000)).copyTo(map); //Extracting Initial Region of Interest for the window and storing it in the matrix
    Player.draw(map);
    imshow(windowName, map);
    cout << "\nZaladowano mape.";
    mapSpeed = 6;  
    mapPosition = 0;
    mapMilestone = 0; 
    score = 0;
    //^ Initial variable values, used in Game::runMap()
    Player.currentHP = Player.maxHP;
    Player.posX = 500;
    Player.posY = 100;
    pressedKey = -1;
    for (int i = 0; i < 50; i++)
    {
        entity[i].exists = false;
        entity[i].positionY = -50;
    }
    waitKey(1);
}

void Game::runMap()
{
    src(Range(10000 - mapPosition, 11000 - mapPosition), Range(0, 1000)).copyTo(map);
    
    Player.draw(map); //RYSOWANIE POSTACI
    //ODCZYT KLAWIATURY
    //pressedKey = waitKey(1);
        if (pressedKey == 'w' && Player.posY <=990) {
            Player.posY += 6;
        } else if (pressedKey == 's' && Player.posY >=10) {
            Player.posY -= 10;
        } else if (pressedKey == 'd' && Player.posX <=990) {
            Player.posX += 15;
        } else if (pressedKey == 'a' && Player.posX >=10) {
            Player.posX -= 15;
        }
  //KONIEC ODCZYTU Z KLAWIATURY

    for (int i = 0; i < 50; i++) //RYSOWANIE ENTITIES
    {
        if (entity[i].exists == true)
            entity[i].drawSelf(map);

        if (entity[i].progress < 1050)
            entity[i].progress += mapSpeed;
        else
        {
            entity[i].exists = false;
        }
    }

    rectangle(map, Point(900, 0), Point(1000, 40), Scalar(0,0,0), FILLED);
    rectangle(map, Point(905, 5), Point(995, 35), Scalar(255, 255, 255), FILLED);
    putText(map, to_string(score), Point(910, 30), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
 

    imshow(windowName, map);
    mapPosition += mapSpeed;
    if(mapPosition >=10000)
        mapPosition -= 10000;

    //cout << "\nPozycja mapy: " << mapPosition;
    score += (double)mapSpeed/100;
    //cout << "\nWYNIK: " << (int)score;
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

void Game::checkCollisions() {}

void Game::checkCollisions(int i)
{

    if(abs(Player.posX-entity[i].positionX) <= 100 && abs(1000-Player.posY-(entity[i].positionY+entity[i].progress)) <= 100 && entity[i].exists==true)
    {
        cout << "\nKOLIZJA na: " << mapPosition << " z: " << entity[i].identifier;
        entity[i].exists = false;
        if (entity[i].identifier == "block" && Player.isInvincible == false)
        {
            Player.currentHP -= 1;
            cout << "\nHP: " << Player.currentHP << "/" << Player.maxHP;
        } else
            cout << "\ninvincibleTimer: " << Player.invincibleTimer;
        if (entity[i].identifier == "koronawirus" && Player.isInvincible == false)
        {
            Player.currentHP -= 2;
            cout << "\nHP: " << Player.currentHP << "/" << Player.maxHP;
        } else
            cout << "\ninvincibleTimer: " << Player.invincibleTimer;
        if (entity[i].identifier == "accel")
        {
            mapSpeed += 2;
            cout << "\nmapSpeed: " << mapSpeed;
        }else 
        if (entity[i].identifier == "brake")
        {
            mapSpeed -= 2;
            if (mapSpeed < 6)
                mapSpeed = 6;
            cout << "\nmapSpeed: " << mapSpeed;
        } else
        if (entity[i].identifier == "pill")
        {
            Player.currentHP += 3;
            if (Player.currentHP > Player.maxHP)
                Player.currentHP = Player.maxHP;
            cout << "\nHP: " << Player.currentHP << "/" << Player.maxHP;
        } else
        if (entity[i].identifier == "mask")
        {
            Player.isInvincible = true;
            Player.invincibleTimer = 200;
            cout << "\ninvincibleTimer: " << Player.invincibleTimer;
        }
    
    }
}

string Game::endGame()
{
    if (highScore < score)
    {
        highScore = score;
        highScoreHolder = Player.characterName;
    }
    rectangle(map, Point(200, 200), Point(800, 800), Scalar(0, 0, 128), FILLED, 0);
    putText(map, "KONIEC GRY", Point(220, 320), FONT_HERSHEY_COMPLEX, 2.7, Scalar(255, 255, 255), 1, 8, false);
    putText(map, "Imie postaci: " + Player.characterName, Point(220, 400), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 1, 8, false);
    putText(map, "Twoj wynik: " + to_string((int)score), Point(220, 470), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 1, 8, false);
    putText(map, "Najlepszy wynik: " + to_string((int)highScore), Point(220, 540), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 1, 8, false);
    putText(map, "Wlasciciel rekordu: " + highScoreHolder, Point(220, 610), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 1, 8, false);
    putText(map, "Escape - Wyjscie  Spacja - restart.", Point(250, 750), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 1, 8, false);
    imshow(windowName, map);
    while (true)
    {
        int key = waitKey();
        if (key == 32)
            return "restart";
        else if (key == 27)
            return "escape";
    }
    
}
