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
    Koronaferie.initializeMap();

    while (true)
    {
        Koronaferie.runMap();

       if (waitKey(1) == 32) //Pressing space
        {
            string input = Koronaferie.pauseGame();
            if (input == "Escape")
                return 0;
       }
    }


    return 0;
}