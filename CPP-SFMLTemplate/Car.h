#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <iostream>

//Compiler Directives
using namespace sf;
using namespace std;
static int CheckPointsLvl1[10][2] =  {
		327, 784,
		611, 349,
		938, 275,
		1293, 395,
		1499, 748,
		1501, 2398,
		1366, 2701,
		957, 2887,
		587, 2804,
		337, 2474
	};

class Car
{

public: 
	float x,y; //Original Values
	float speed;
	float angle;
	int CurrentCheckPoint;

public:
	void CarValues(float X,float Y, float Speed, float Angle) //Storing the initial values
	{
		x = X;
		y = Y;
		speed = Speed;
		angle = Angle;
		CurrentCheckPoint = 0;
	}

	void CarPos(float X, float Y) //Increasing or descreasing the initial values
	{
		x = X;
		y = Y;
	}

	void NextCheckPoint ()
	{
		int xcp = CheckPointsLvl1[CurrentCheckPoint][0]; //Current Checkpoint = X (902) xcp = x checkpoint
		int ycp = CheckPointsLvl1[CurrentCheckPoint][1]; //Current Checkpoint = Y (1019) ycp = y checkpoint

		float beta = angle-atan2(xcp-x,-ycp+y);

		if (sin(beta)<0) angle+=0.005*speed;
		else angle-=0.005*speed;

		if ((x-xcp)*(x-xcp)+(y-ycp)*(y-ycp)<25*25) CurrentCheckPoint=(CurrentCheckPoint+1)%10; //X/Y coordinates of the car moves towards the current checkpoint
	}

	void CarMove()
	{
		x += sin(angle) * speed; //Allows the vehicle to travel on the X coordinates
		y -= cos(angle) * speed; //Allows the vehicle to travel on the Y coordinates
	}
};
