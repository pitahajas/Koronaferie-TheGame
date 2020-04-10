#include "MainWindow.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<Windows.h>

using namespace std;
using namespace cv;

//Inicjalizacja głównego okna, w którym będzie wyświetlana gra
void MainWindow::Initialize()
{
	ifstream configReader;

	configReader.open("config.txt");
	if (configReader.fail()) {
		cout << "DEBUG: Missing file: config.txt";
	}

	while (!configReader.eof())
	{

	}
}

void MainWindow::setResolution() {

	cout << "Wprowadz wysokosc tworzonego okna:";
	cin >> resolutionHeigth;
	cout << "Wprowadz szerokosc tworzonego okna:";
	cin >> resolutionWidth;

}

void MainWindow::setResolution(int heigth, int width) {

	resolutionHeigth = heigth;
	resolutionWidth = width;

}

void MainWindow::setWindowName(string Name) {

windowName = Name;

}

void MainWindow::makeWindow() {

	Mat window = Mat(resolutionHeigth, resolutionWidth, CV_16U);
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
}

void MainWindow::showWelcome() {

	

}

