#include "MakeWindow.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<Windows.h>

using namespace std;
using namespace cv;

void MakeWindow::setResolution() {

	cout << "Wprowadz wysokosc tworzonego okna:";
	cin >> resolutionHeigth;
	cout << "Wprowadz szerokosc tworzonego okna:";
	cin >> resolutionWidth;

}

void MakeWindow::setResolution(int heigth, int width) {

	resolutionHeigth = heigth;
	resolutionWidth = width;

}

void MakeWindow::setWindowName(string Name) {

windowName = Name;

}

void MakeWindow::makeWindow() {

	Mat window = Mat(resolutionHeigth, resolutionWidth, CV_16U);
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
}

void MakeWindow::showWelcome() {

	

}

