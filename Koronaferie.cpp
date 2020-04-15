#include<opencv2/opencv.hpp>
#include<iostream>
#include<windows.h>
#include "MainWindow.h"

using namespace std;
using namespace cv;

int main()
{

    MainWindow mainWindow;

    mainWindow.initialize(); //Initialization of the main game window
    mainWindow.showWelcomeScreen(); //Displaying welcome animation loop
    mainWindow.chooseCharacter();

    return 0;
}