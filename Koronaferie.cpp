#include<opencv2/opencv.hpp>
#include<iostream>
#include<windows.h>
#include "Game.h"

using namespace std;
using namespace cv;

int main()
{

    Game Koronaferie;

    Koronaferie.initialize(); //Initialization of the main game window
    Koronaferie.showWelcomeScreen(); //Displaying welcome animation loop
    Koronaferie.highScore = 0;
    Launch:
    Koronaferie.chooseCharacter();
    Koronaferie.initializeGame();

    int randomizer;
    int pressedKey;

    while (true)
    {
        Koronaferie.runMap();
        for (int i = 0; i < 50; i++)
        {
            if (rand() % 1000 < 2 && Koronaferie.entity[i].exists == false)
            {
                randomizer = rand() % 200;
                if(randomizer <30)
                    Koronaferie.entity[i].spawnEntity("block");
                else if(randomizer >=30 && randomizer <45)
                    Koronaferie.entity[i].spawnEntity("koronawirus");
                else if (randomizer >= 45 && randomizer < 65)
                    Koronaferie.entity[i].spawnEntity("accel");
                else if (randomizer >= 65 && randomizer < 85)
                    Koronaferie.entity[i].spawnEntity("brake");
                else if (randomizer >= 85 && randomizer < 95)
                    Koronaferie.entity[i].spawnEntity("pill");
                else if (randomizer >= 95 && randomizer <= 100)
                    Koronaferie.entity[i].spawnEntity("mask");
            }


            Koronaferie.checkCollisions(i);
        }

        pressedKey = waitKey(1);

        if (pressedKey == 32) //Pressing space

        {
            if (Koronaferie.pauseGame() == "Escape")
                return 0;
        }
        else if (pressedKey == 'w' || pressedKey == 'a' || pressedKey == 's' || pressedKey == 'd')
        {
            cout << "\nPressedKey: " << pressedKey;
            Koronaferie.pressedKey = pressedKey;
        }
        if (Koronaferie.Player.currentHP <= 0)
        {
            if(Koronaferie.endGame()=="escape")
                return 0;
            else
                goto Launch;
        }
    }


    return 0;
}