#include<opencv2/opencv.hpp>
#include<iostream>
#include<windows.h>
#include "Game.h"

using namespace std;
using namespace cv;

int main()
{

    Game Koronaferie;
    int pressedKey;

    Koronaferie.initialize(); //Initialization of the main game window
    Koronaferie.showWelcomeScreen(); //Displaying welcome animation loop
    Koronaferie.highScore = 0;

    do
    {
        Koronaferie.chooseCharacter();
        Koronaferie.initializeGame();

        while (true)
        {
            Koronaferie.runGame();

            pressedKey = waitKey(1);

            if (pressedKey == 32) //Pressing space
            {
                if (Koronaferie.pauseGame() == "Escape")
                    return 0;
            }
            else if (pressedKey == 'w' || pressedKey == 'a' || pressedKey == 's' || pressedKey == 'd')
            {
                cout << "INPUT: " << pressedKey;
                Koronaferie.pressedKey = pressedKey;
            }

            if (Koronaferie.isPlayerDead() == true)
            {
                break;
            }
        }

    } while (Koronaferie.endGame() != "escape");

    return 0;
}