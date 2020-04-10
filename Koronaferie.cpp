#include<opencv2/opencv.hpp>
#include<iostream>
#include<windows.h>
#include "MakeWindow.h"

using namespace std;
using namespace cv;

int main()
{
    MakeWindow mainWindow;
    mainWindow.setResolution(1000,1000);
    mainWindow.setWindowName("Koronaferie");
    mainWindow.makeWindow();
    

    waitKey(0);
    return 0;
}