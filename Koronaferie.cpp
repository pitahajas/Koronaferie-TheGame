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

    while (waitKey(1)!=32)
        Koronaferie.runMap();

    return 0;
}