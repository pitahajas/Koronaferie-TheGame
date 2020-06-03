#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;
using namespace cv;

class Character
{
public:
	Character();

	string characterName;
	int characterSkin;
	int posX;
	int posY;
	int maxHP;
	int currentHP;

	bool isInvincible;
	int invincibleTimer;

	void draw(Mat mapinput);
	bool checkCollision(int obstaclePositionX, int obstaclePositionY, string obstacleIdentifier, int mapPosition, int mapSpeed);

private:


};