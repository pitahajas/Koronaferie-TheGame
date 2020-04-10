#include<opencv2/opencv.hpp>
#include<iostream>
#include<windows.h>
#include "MainWindow.h"

using namespace std;
using namespace cv;

int main()
{

    MainWindow mainWindow;
    mainWindow.Initialize();

    waitKey(0); //DEBUG ONLY
    return 0;
}