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
    initializeVariables();

    src = imread("Map.jpg", IMREAD_COLOR); // storing the full map in a matrix
    src(Range(10000, 11000), Range(0, 1000)).copyTo(map); // extracting initial fragment of the full map and storing it in the 'map' matrix
    Player.draw(map); // drawing player character

    entity->removeAllEntities();

    showTutorial(map);

    imshow(windowName, map);
    cout << "\nZaladowano mape.";

    waitKey();
}

void Game::initializeVariables()
{
    this->mapSpeed = 6;
    this->mapPosition = 0;
    this->mapMilestone = 0;
    this->score = 0;
    this->Player.currentHP = Player.maxHP;
    this->Player.posX = 500;
    this->Player.posY = 100;
    this->pressedKey = -1;
}

void Game::showTutorial(Mat map)
{
    rectangle(map, Point(200, 450), Point(800, 550), Scalar(0, 0, 128), FILLED);
    putText(map, "A,W,D,S - sterowanie postacia.", Point(220, 480), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
    putText(map, "Wcisnij dowolny przycisk, by rozpoczac rozgrywke.", Point(220, 520), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
}

void Game::runGame()
{
    // redrawing map
    src(Range(10000 - mapPosition, 11000 - mapPosition), Range(0, 1000)).copyTo(map);

    Player.draw(map);

    readInput(pressedKey);

    for (int i = 0; i < 50; ++i)
    {
        entity->randomizeEntity(i);
        checkCollisions(i);

    }

    entity->drawAllEntities(map, mapSpeed);

    drawScoreBox(map, score);

    imshow(windowName, map);

    updateVariables();


    Sleep(10);
}

void Game::readInput(int pressedKey)
{
    // reading keyboard input

    switch (pressedKey)
    {
    case 'w':
        if (Player.posY <= 990)
            this->Player.posY += 6;
        break;
    case 's':
        if (Player.posY >= 10)
            this->Player.posY -= 10;
        break;
    case 'd':
        if (Player.posX <= 990)
            this->Player.posX += 15;
        break;
    case 'a':
        if (Player.posX >= 10)
            this->Player.posX -= 15;
        break;
    }
}

void Game::drawScoreBox(Mat map, double score)
{
    rectangle(map, Point(900, 0), Point(1000, 40), Scalar(0, 0, 0), FILLED);
    rectangle(map, Point(905, 5), Point(995, 35), Scalar(255, 255, 255), FILLED);
    putText(map, to_string(score), Point(910, 30), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
}

void Game::updateVariables()
{
    this->mapPosition += mapSpeed;

    // looping the map
    if (mapPosition >= 10000)
        this->mapPosition -= 10000;

    // tracking score and converting to metres
    this->score += (double)mapSpeed / 100;

    // tracking milestones every 1000 pixels for speed incrementation.
    this -> mapMilestone += this->mapSpeed;
    if (this->mapMilestone >= 1000)
    {
        this->mapSpeed += 1;
        this->mapMilestone -= 1000;
        cout << "\nMAP SPEED +1 = " << this->mapSpeed;
    }

    // tracking player invincibility time
    if (Player.invincibleTimer > 0)
        this->Player.invincibleTimer -= 1;
    else
        this->Player.isInvincible = false;
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

void Game::checkCollisions(int loopCounter)
{

    if (abs(Player.posX - entity[loopCounter].positionX) <= 100 && abs(1000 - Player.posY - (entity[loopCounter].positionY + entity[loopCounter].progress)) <= 100 && entity[loopCounter].exists == true)
    {
        cout << "\nKOLIZJA na: " << mapPosition << " z: " << entity[loopCounter].identifier;
        entity[loopCounter].exists = false;
        if (entity[loopCounter].identifier == "block" && Player.isInvincible == false)
        {
            Player.currentHP -= 1;
            cout << "\nHP: " << Player.currentHP << "/" << Player.maxHP;
        }
        else
            cout << "\ninvincibleTimer: " << Player.invincibleTimer;
        if (entity[loopCounter].identifier == "koronawirus" && Player.isInvincible == false)
        {
            Player.currentHP -= 2;
            cout << "\nHP: " << Player.currentHP << "/" << Player.maxHP;
        }
        else
            cout << "\ninvincibleTimer: " << Player.invincibleTimer;
        if (entity[loopCounter].identifier == "accel")
        {
            mapSpeed += 2;
            cout << "\nmapSpeed: " << mapSpeed;
        }
        else
            if (entity[loopCounter].identifier == "brake")
            {
                mapSpeed -= 2;
                if (mapSpeed < 6)
                    mapSpeed = 6;
                cout << "\nmapSpeed: " << mapSpeed;
            }
            else
                if (entity[loopCounter].identifier == "pill")
                {
                    Player.currentHP += 3;
                    if (Player.currentHP > Player.maxHP)
                        Player.currentHP = Player.maxHP;
                    cout << "\nHP: " << Player.currentHP << "/" << Player.maxHP;
                }
                else
                    if (entity[loopCounter].identifier == "mask")
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
        int key = waitKey(20);
        if (key == 32)
            return "restart";
        else if (key == 27)
            return "escape";
    }

}

bool Game::isPlayerDead()
{
    if (Player.currentHP <= 0)
        return true;
    else
        return false;
}
