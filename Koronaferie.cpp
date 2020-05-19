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
    Koronaferie.chooseCharacter();

    Entities entity;
    Koronaferie.initializeMap();

    int randomizer;

    while (true)
    {
        Koronaferie.runMap();
        for (int i = 0; i < 50; i++)
        {
            if (rand() % 1000 < 2 && Koronaferie.entity[i].exists == false)
            {
                randomizer = rand() % 100;
                if(randomizer <30)
                    Koronaferie.entity[i].spawnEntity("block");
                else if(randomizer >=30 && randomizer <55)
                    Koronaferie.entity[i].spawnEntity("koronawirus");
                else if (randomizer >= 55 && randomizer < 70)
                    Koronaferie.entity[i].spawnEntity("accel");
                else if (randomizer >= 70 && randomizer < 85)
                    Koronaferie.entity[i].spawnEntity("brake");
                else if (randomizer >= 85 && randomizer < 95)
                    Koronaferie.entity[i].spawnEntity("pill");
                else if (randomizer >= 95 && randomizer <= 100)
                    Koronaferie.entity[i].spawnEntity("mask");
            }

        }

       if (waitKey(1) == 32) //Pressing space

        {
            if (Koronaferie.pauseGame() == "Escape")
                return 0;
       }
    }


    return 0;
}