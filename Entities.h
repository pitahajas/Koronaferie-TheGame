#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;
using namespace cv;

class Entities
{
public:
	Entities();
	Entities(int id);

	void spawnEntity();
	void spawnEntity(string id);

	void drawSelf();
	void drawSelf(Mat map);

	int progress;
	int positionX;
	int positionY;
	bool exists;

	string identifier;

private:
	int positionX;
	int positionY;

};
