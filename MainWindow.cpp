#include "MainWindow.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include <windows.h>
#include<filesystem>

using namespace std;
using namespace cv;



void MainWindow::Initialize()   //Initialization of main game window.
{
        ConfigRead(); //Setting up and reading window configuration from text file.

        Mat window = Mat(resolutionHeigth, resolutionWidth, CV_16U); //Creating Mat Matrix of resolution set in Config.txt
        imshow(windowName, window);

}

void MainWindow::ConfigRead()
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
    }
    else
    {
        cout << "DEBUG INFO: Cos poszlo nie tak z otwarciem pliku Config.txt" << endl;
    }
    configReader.close(); //Closing Config.txt file
}

void MainWindow::ShowWelcomeScreen() {

    while (true) //Image animation loop
    {

        for (int frameCounter = 1; frameCounter <= 6; frameCounter++) {

            imshow(windowName, imread("menu" + to_string(frameCounter) + ".jpg", CV_LOAD_IMAGE_COLOR));
            if (cvWaitKey(50) == 13) //if ENTER is pressed, kill animation loop.
            {
                return;
            }

        }
        
    }
        
}

