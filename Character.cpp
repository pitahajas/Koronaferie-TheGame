#include "Game.h"
#include "CharacterChoiceWindow.h"

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
                invincibleTimer = 400; //100 ~= 1 sekunda
                cout << "\ninvincibleTimer: " << invincibleTimer;
            }
                return true;
    }
    else return false;
}

void Character::draw(Mat mapinput) {

    //DRAWING "KRYSTIAN BANAN" - SKIN 1
    if (characterSkin == 1) {
        Point czupryna[1][14]; //Initialize array of points

        //Declare new points positions of hair polygon
        czupryna[0][0] = Point(posX, 1000 - posY - 90);
        czupryna[0][1] = Point(posX + 10, 1000 - posY - 40);
        czupryna[0][2] = Point(posX + 60, 1000 - posY - 40);
        czupryna[0][3] = Point(posX + 30, 1000 - posY - 20);
        czupryna[0][4] = Point(posX + 60, 1000 - posY);
        czupryna[0][5] = Point(posX + 25, 1000 - posY + 20);
        czupryna[0][6] = Point(posX + 35, 1000 - posY + 60);
        czupryna[0][7] = Point(posX, 1000 - posY + 50);
        czupryna[0][8] = Point(posX - 35, 1000 - posY + 60);
        czupryna[0][9] = Point(posX - 25, 1000 - posY + 20);
        czupryna[0][10] = Point(posX - 60, 1000 - posY);
        czupryna[0][11] = Point(posX - 30, 1000 - posY - 20);
        czupryna[0][12] = Point(posX - 60, 1000 - posY - 40);
        czupryna[0][13] = Point(posX - 10, 1000 - posY - 40);

        const Point* ppt[1] = { czupryna[0] };
        int npt[] = { 14 };

        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(255, 204, 204), FILLED);
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(0, 0, 0), 1);
        line(mapinput, Point(posX + 10, 950 - posY), Point(posX + 35, 950 - posY), Scalar(255, 0, 0), 2);
        line(mapinput, Point(posX - 10, 950 - posY), Point(posX - 35, 950 - posY), Scalar(255, 0, 0), 2);
        line(mapinput, Point(posX + 35, 950 - posY), Point(posX + 45, 1000 - posY), Scalar(255, 0, 0), 2);
        line(mapinput, Point(posX - 35, 950 - posY), Point(posX - 45, 1000 - posY), Scalar(255, 0, 0), 2);
        fillPoly(mapinput, ppt, npt, 1, Scalar(0, 255, 255), LINE_8);
    }

    //DRAWING "HERY PIOTER" - SKIN 2
    if (characterSkin == 2) {
        //body
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(188, 231, 255), FILLED);
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(0, 0, 0), 1);
        //eyeballs
        circle(mapinput, Point(posX + 15, 975 - posY), 5, Scalar(255, 255, 255), FILLED);
        circle(mapinput, Point(posX - 15, 975 - posY), 5, Scalar(255, 255, 255), FILLED);
        //glasses
        circle(mapinput, Point(posX + 15, 975 - posY), 10, Scalar(215, 55, 16), 2);
        circle(mapinput, Point(posX - 15, 975 - posY), 10, Scalar(215, 55, 16), 2);
        line(mapinput, Point(posX - 5, 975 - posY), Point(posX + 5, 975 - posY), Scalar(215, 55, 16), 2);
        //pupils
        circle(mapinput, Point(posX + 16, 970 - posY), 3, Scalar(0, 0, 0), FILLED);
        circle(mapinput, Point(posX - 16, 972 - posY), 3, Scalar(0, 0, 0), FILLED);
        //scar
        line(mapinput, Point(posX - 35, 990 - posY), Point(posX - 30, 985 - posY), Scalar(0,0, 215), 2);
        line(mapinput, Point(posX - 30, 985 - posY), Point(posX - 40, 980 - posY), Scalar(0, 0, 215), 2);
        line(mapinput, Point(posX - 40, 980 - posY), Point(posX - 30, 975 - posY), Scalar(0, 0, 215), 2);
        //mounth
        line(mapinput, Point(posX - 7, 960 - posY), Point(posX + 7, 960 - posY), Scalar(20, 20, 20), 1);
        //hair
        Point czupryna[1][10]; 

        //Declare new points positions of hair polygon
        czupryna[0][0] = Point(posX + 60, 1000 - posY - 20);
        czupryna[0][1] = Point(posX + 30, 1000 - posY);
        czupryna[0][2] = Point(posX + 60, 1000 - posY + 20);
        czupryna[0][3] = Point(posX + 25, 1000 - posY + 40);
        czupryna[0][4] = Point(posX + 35, 1000 - posY + 100);
        czupryna[0][5] = Point(posX, 1000 - posY + 70);
        czupryna[0][6] = Point(posX - 35, 1000 - posY + 100);
        czupryna[0][7] = Point(posX - 25, 1000 - posY + 40);
        czupryna[0][8] = Point(posX - 60, 1000 - posY + 20);
        czupryna[0][9] = Point(posX - 30, 1000 - posY);

        const Point* ppt[1] = { czupryna[0] };
        int npt[] = { 10 };

        fillPoly(mapinput, ppt, npt, 1, Scalar(0, 51, 102), LINE_8);
    }

    //DRAWING "KAKUB NIEJANICKI" - SKIN 3
    if (characterSkin == 3) {
        //body
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(204, 204, 255), FILLED);
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(0, 0, 0), 1);
        //eyeballs
        circle(mapinput, Point(posX + 15, 975 - posY), 8, Scalar(0, 255, 0), FILLED);
        circle(mapinput, Point(posX - 15, 975 - posY), 8, Scalar(0, 255, 0), FILLED);
        //pupils
        circle(mapinput, Point(posX + 16, 970 - posY), 3, Scalar(0, 0, 0), FILLED);
        circle(mapinput, Point(posX - 16, 970 - posY), 3, Scalar(0, 0, 0), FILLED);
        //hat
        circle(mapinput, Point(posX, 1020 - posY), 30, Scalar(0, 0, 255), FILLED);
        circle(mapinput, Point(posX, 1020 - posY), 30, Scalar(0, 0, 0), 2);
        circle(mapinput, Point(posX, 1022.5 - posY), 25, Scalar(50, 50, 255), FILLED);
        circle(mapinput, Point(posX, 1022.5 - posY), 25, Scalar(0, 0, 0), 1);
        circle(mapinput, Point(posX, 1025 - posY), 20, Scalar(0, 0, 150), FILLED);
        circle(mapinput, Point(posX, 1025 - posY), 20, Scalar(0, 0, 0), 1);
        //mounth
        line(mapinput, Point(posX - 7, 960 - posY), Point(posX + 7, 960 - posY), Scalar(20, 20, 20), 1);
        line(mapinput, Point(posX - 7, 958 - posY), Point(posX - 7, 962 - posY), Scalar(20, 20, 20), 1);
        line(mapinput, Point(posX + 7, 958 - posY), Point(posX + 7, 962 - posY), Scalar(20, 20, 20), 1);
    }

    //DRAWING "DIABE£EK" - SKIN 4
    if (characterSkin == 4) {
        //body
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(0, 0, 200), FILLED);
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(0, 0, 0), 1);
        //eyeballs
        circle(mapinput, Point(posX + 15, 975 - posY), 8, Scalar(200, 200, 255), FILLED);
        circle(mapinput, Point(posX - 15, 975 - posY), 8, Scalar(200, 200, 255), FILLED);
        //pupils
        circle(mapinput, Point(posX + 16, 970 - posY), 4, Scalar(0, 0, 255), FILLED);
        circle(mapinput, Point(posX + 16, 970 - posY), 4, Scalar(0, 0, 0), 1);
        circle(mapinput, Point(posX - 16, 970 - posY), 4, Scalar(0, 0, 255), FILLED);
        circle(mapinput, Point(posX - 16, 970 - posY), 4, Scalar(0, 0, 0), 1);
        //horns
        line(mapinput, Point(posX + 25, 990 - posY), Point(posX + 40, 985 - posY), Scalar(0, 0, 100), 2);
        line(mapinput, Point(posX + 40, 985 - posY), Point(posX + 30, 1000 - posY), Scalar(0, 0, 150), 2);
        line(mapinput, Point(posX - 25, 990 - posY), Point(posX - 40, 985 - posY), Scalar(0, 0, 100), 2);
        line(mapinput, Point(posX - 40, 985 - posY), Point(posX - 30, 1000 - posY), Scalar(0, 0, 150), 2);
        //tail
        line(mapinput, Point(posX, 1020 - posY), Point(posX + 15, 1040 - posY), Scalar(0, 0, 80), 3);
        line(mapinput, Point(posX + 15, 1040 - posY), Point(posX - 20, 1050 - posY), Scalar(0, 0, 120), 3);
        line(mapinput, Point(posX - 20, 1050 - posY), Point(posX, 1065 - posY), Scalar(0, 0, 80), 3);
        line(mapinput, Point(posX, 1065 - posY), Point(posX - 3, 1055 - posY), Scalar(0, 0, 100), 3);
        line(mapinput, Point(posX, 1065 - posY), Point(posX - 8, 1065 - posY), Scalar(0, 0, 130), 3);
        //mounth
        line(mapinput, Point(posX - 7, 958 - posY), Point(posX - 4, 962 - posY), Scalar(20, 20, 20), 1);
        line(mapinput, Point(posX - 4, 962 - posY), Point(posX, 955 - posY), Scalar(20, 20, 20), 1);
        line(mapinput, Point(posX, 955 - posY), Point(posX + 2, 964 - posY), Scalar(20, 20, 20), 1);
        line(mapinput, Point(posX + 2, 964 - posY), Point(posX + 7, 959 - posY), Scalar(20, 20, 20), 1);
    }

    //DRAWING "ANIO£EK" - SKIN 5
    if (characterSkin == 5) {
        //body
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(255, 255, 100), FILLED);
        circle(mapinput, Point(posX, 1000 - posY), 50, Scalar(0, 0, 0), 1);
        //eyeballs
        circle(mapinput, Point(posX + 15, 975 - posY), 8, Scalar(255, 255, 255), FILLED);
        circle(mapinput, Point(posX - 15, 975 - posY), 8, Scalar(255, 255, 255), FILLED);
        //pupils
        circle(mapinput, Point(posX + 16, 970 - posY), 4, Scalar(255, 128, 0), FILLED);
        circle(mapinput, Point(posX - 16, 970 - posY), 4, Scalar(255, 128, 0), FILLED);
        //wings
        line(mapinput, Point(posX + 30, 995 - posY), Point(posX + 50, 1000 - posY), Scalar(0, 255, 255), 5);
        line(mapinput, Point(posX + 30, 998 - posY), Point(posX + 60, 1010 - posY), Scalar(20, 230, 255), 5);
        line(mapinput, Point(posX + 30, 1003 - posY), Point(posX + 60, 1020 - posY), Scalar(40, 210, 255), 5);
        line(mapinput, Point(posX - 30, 995 - posY), Point(posX - 50, 1000 - posY), Scalar(0, 255, 255), 5);
        line(mapinput, Point(posX - 30, 998 - posY), Point(posX - 60, 1010 - posY), Scalar(20, 230, 255), 5);
        line(mapinput, Point(posX - 30, 1003 - posY), Point(posX - 60, 1020 - posY), Scalar(40, 210, 255), 5);
        //aura ring
        circle(mapinput, Point(posX, 1022 - posY), 30, Scalar(0, 200, 230), 2);
        circle(mapinput, Point(posX, 1020 - posY), 30, Scalar(40, 255, 255), 2);
        //mounth
        line(mapinput, Point(posX - 7, 960 - posY), Point(posX, 958 - posY), Scalar(0, 0, 255), 2);
        line(mapinput, Point(posX, 958 - posY), Point(posX + 7, 960 - posY), Scalar(0, 0, 255), 2);
    }

    //health bar gui
    rectangle(mapinput, Point(posX - 50, 900 - posY), Point(posX - 50 + 10*maxHP, 910-posY), Scalar(0, 0, 255), FILLED);
    rectangle(mapinput, Point(posX - 50, 900 - posY), Point(posX - 50 + 10 * currentHP, 910 - posY), Scalar(128, 255, 0), FILLED);
    
    return;
}
