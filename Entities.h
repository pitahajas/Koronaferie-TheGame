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

	void drawAllEntities(Mat map, int mapSpeed);
	void removeAllEntities();
	void randomizeEntity(int loopCounter);

	int positionX;
	int positionY;
	bool exists;

	string identifier;

private:

	void drawSelf(Mat map);
	void spawnEntity(string name);

};
