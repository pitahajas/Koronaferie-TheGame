#include "Game.h"

#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>

using namespace std;
using namespace cv;

Character::Character()
{
	posX = 500;
	posY = 100;
	maxHP = 10;
	currentHP = 10;
	characterSkin = 3;

	isInvincible = false;
	invincibleTimer = 0;
}

bool Character::checkCollision(int obstaclePositionX, int obstaclePositionY, string obstacleIdentifier, int mapPosition, int mapSpeed)
{
    if (abs(posX - obstaclePositionX) <= 100 && abs(1000 - posY - (obstaclePositionY)) <= 100)
    {
        cout << "\nKOLIZJA na: " << mapPosition << " z: " << obstacleIdentifier;
        if (obstacleIdentifier == "block" && isInvincible == false)
        {
            currentHP -= 1;
            cout << "\nHP: " << currentHP << "/" << maxHP;
        }
        else
            cout << "\ninvincibleTimer: " << invincibleTimer;
        if (obstacleIdentifier == "koronawirus" && isInvincible == false)
        {
            currentHP -= 2;
            cout << "\nHP: " << currentHP << "/" << maxHP;
        }
        else
            cout << "\ninvincibleTimer: " << invincibleTimer;
        if (obstacleIdentifier == "pill")
        {
            currentHP += 3;
            if (currentHP > maxHP)
                currentHP = maxHP;
            cout << "\nHP: " << currentHP << "/" << maxHP;
        }
        else
            if (obstacleIdentifier == "mask")
            {
                isInvincible = true;
                invincibleTimer = 200;
                cout << "\ninvincibleTimer: " << invincibleTimer;
            }
                return true;
    }
    else return false;
}

void Character::draw(Mat mapinput) {


		Point czupryna[1][14];

		czupryna[0][0] = Point(posX, 1000 - posY + 70);
		czupryna[0][1] = Point(posX + 10, 1000 - posY + 20);
		czupryna[0][2] = Point(posX + 60, 1000 - posY + 20);
		czupryna[0][3] = Point(posX + 30, 1000 - posY);
		czupryna[0][4] = Point(posX + 60, 1000 - posY - 20);
		czupryna[0][5] = Point(posX + 25, 1000 - posY - 40);
		czupryna[0][6] = Point(posX + 35, 1000 - posY - 100);
		czupryna[0][7] = Point(posX, 1000 - posY - 70);
		czupryna[0][8] = Point(posX - 35, 1000 - posY - 100);
		czupryna[0][9] = Point(posX - 25, 1000 - posY - 40);
		czupryna[0][10] = Point(posX - 60, 1000 - posY - 20);
		czupryna[0][11] = Point(posX - 30, 1000 - posY);
		czupryna[0][12]= Point(posX - 60, 1000 - posY + 20);
		czupryna[0][13]= Point(posX - 10, 1000 - posY + 20);

		const Point* ppt[1] = { czupryna[0] };
		int npt[] = { 14 };

        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(255, 204, 204), FILLED);
		line(mapinput, Point(posX + 10, 950 - posY), Point(posX + 35, 950 - posY), Scalar(255, 0, 0), 2);
		line(mapinput, Point(posX - 10, 950 - posY), Point(posX - 35, 950 - posY), Scalar(255, 0, 0), 2);
		line(mapinput, Point(posX + 35, 950 - posY), Point(posX + 45, 1000 - posY), Scalar(255, 0, 0), 2);
		line(mapinput, Point(posX - 35, 950 - posY), Point(posX - 45, 1000 - posY), Scalar(255, 0, 0), 2);
		fillPoly(mapinput, ppt, npt, 1, Scalar(0, 255, 255),LINE_8);
		rectangle(mapinput, Point(posX - 50, 900 - posY), Point(posX - 50 + 10*maxHP, 910-posY), Scalar(0, 0, 255), FILLED);
		rectangle(mapinput, Point(posX - 50, 900 - posY), Point(posX - 50 + 10*currentHP, 910 - posY), Scalar(128, 255, 0), FILLED);

    return;
}