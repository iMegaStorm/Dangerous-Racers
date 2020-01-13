//Header Files
#include <iostream>
#include <SFML/Graphics.hpp>
#include "LoadAssets.h"
#include "Car.h"

//Compiler Directives
using namespace std;
using namespace sf;

//Global Variables
	//Game Window Variables...
	RenderWindow window(VideoMode(800, 500),"Dangerous Racers",Style::Titlebar);

	//Variable of the header class type, that helps us to load images
	LoadAssets loadAssets; 
	Car car;
	Car van;
	Car audi;
	Car mustang;

//Game Screen Variables
	//Assigns a value for each screen
	const int GAME_MENU_SCREEN = 0; //Main game screen
	const int INSTRUCTIONS_MENU_SCREEN = 1;
	const int LEVEL_1_SCREEN = 2; //Track 1 of the racing game
	const int LEVEL_2_SCREEN = 3; //Track 2 of the racing game
	int CURRENT_SCREEN = GAME_MENU_SCREEN; //Using current screen in order to switch to another screen whilst drawing
	int Level = 1; //Sets the current level
	int TrackPosX = 0, TrackPosY = 0; //Setting the background position


	const float pi = 3.14159; //Using pie to help with turning
	
	float Speed = 0; //Speed for the cars
	float TurnSpeed = 0.05; //Turn speed for the cars
	float Angle = 0; //Angle for the cars
	float MaxSpeed = 20; //Max speed for the cars

	//Boolean that lets us know the game has started
	bool GameStarted = false;
	bool Instructions = false;

	float Accelerate = 0.2; //Acceleration value for the cars
	float Decelerate = 0.2; //Deceleration value for the cars

	Vector2i MouseCursorLocation(0,0);

	//Sprite Variables
	Sprite Track1Sprite;
	Sprite Track2Sprite;
	Sprite ViperSprite;
	Sprite VanSprite;
	Sprite AudiSprite;
	Sprite MustangSprite;
	Sprite InstructionMenu;
	Sprite PlayButton1;
	Sprite ExitButton1;

void inputs () 
{
	bool W = false, S = false, A = false, D = false;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		W = true;
		if (car.speed < MaxSpeed) //Whilst car speed is lower than MaxSpeed, then Accelerate until you reach MaxSpeed
		{
			car.speed += Accelerate;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) 
	{
		S = true;
		if (car.speed > -MaxSpeed/2) //Whilst car speed is greater than the -MaxSpeed divided by 2 (MaxSpeed is 20/2 = 10), then Decelerate
		{
			car.speed -= Decelerate;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) 
	{
		A = true;
		car.angle -= TurnSpeed * car.speed/MaxSpeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		D = true;
		car.angle += TurnSpeed * car.speed/MaxSpeed;
	}
	if (!W && car.speed > 0)
	{
		car.speed -= Decelerate;
	}
	else if (!W && !S && car.speed < 0) //If the W & S key's aren't pressed and the car speed is 
	{
		car.speed = 0;
	}

	if (mustang.speed < MaxSpeed-1) //If the mustangs speed value is less than the max speed, then do the following:
	{
		mustang.speed += Accelerate; //Increasing the speed of the Mustang
	}

	if (van.speed < MaxSpeed-1) //If the vans speed value is less than the max speed, then do the following:
	{
		van.speed += Accelerate; //Increasing the speed of the van
	}
	
	if (audi.speed < MaxSpeed-1) //If the audis speed value is less than the max speed, then do the following:
	{
		audi.speed += Accelerate; //Increasing the speed of the audi
	}
	
	ViperSprite.setRotation(car.angle*180/pi); //Helps us with how smooth the turning angle is
	ViperSprite.setPosition(window.getSize().x/2, window.getSize().y/2+100); 	//Set the location of the car to the middle of the screen
	
	//Setting the position of all the vechiles
	ViperSprite.setPosition(car.x -TrackPosX, car.y -TrackPosY); 
	AudiSprite.setPosition(audi.x -TrackPosX, audi.y -TrackPosY);
	MustangSprite.setPosition(mustang.x -TrackPosX, mustang.y -TrackPosY);
	VanSprite.setPosition(van.x -TrackPosX, van.y -TrackPosY);
	//cout << mustang.speed << van.speed << audi.speed << "\n" ;
		//CurrentCheckPoint <<' '<< mustang.x << " " << mustang.y<< "\n";
	
	car.x += sin(car.angle) * car.speed; //Allows the vehicle to travel on the X coordinates
	car.y -= cos(car.angle) * car.speed; //Allows the vehicle to travel on the Y coordinates
	
	MustangSprite.setRotation(mustang.angle*180/pi); //Helps us with how smooth the turning angle is
	VanSprite.setRotation(van.angle*180/pi); //Helps us with how smooth the turning angle is
	AudiSprite.setRotation(audi.angle*180/pi); //Helps us with how smooth the turning angle is
	
	mustang.NextCheckPoint(); //Vehicle goes to the next checkpoint
	van.NextCheckPoint(); //Vehicle goes to the next checkpoint
	audi.NextCheckPoint(); //Vehicle goes to the next checkpoint
	
	mustang.CarMove(); //Everything to move the car
	van.CarMove(); //Everything to move the car
	audi.CarMove(); //Everything to move the car

	if (ViperSprite.getGlobalBounds().intersects(AudiSprite.getGlobalBounds()) || ViperSprite.getGlobalBounds().intersects(MustangSprite.getGlobalBounds()) || ViperSprite.getGlobalBounds().intersects(VanSprite.getGlobalBounds()))
	{
		cout << "COLLISION" << "\n";
	}

	if (Level == 1)
	{
		if (car.x > 420 && car.x < 1400) //Make sure the car is in the middle of the screen whilst playing
		{
			TrackPosX = car.x -window.getSize().x/2;
		}
		else if (car.x <= 50) //Makes sure the car doesn't escape the left side of the map
		{
			car.x = 50; //Sets the cars x = 75
			//ViperSprite.setPosition(-TrackPosX + car.x, -TrackPosY + car.y);
		}
		else if (car.x >= 1764) //Makes sure the car doesn't escape the right side of the map
		{
			car.x = 1764; //Sets the cars X = 1764
		}
		if (car.y > 260 && car.y < 2930) //Make sure the car is in the middle of the screen whilst playing
		{
			TrackPosY = car.y -window.getSize().y/2;
		}
		else if (car.y <= 50) //Makes sure the car doesn't escape the top of the map
		{
			car.y = 50; //Sets the cars Y = 100
		}
		else if (car.y >= 3138) //Makes sure the car doesn't escape the bottom of the map
		{
			car.y = 3138; //Sets the cars Y = 3138
		}
	}
	/*if(Mouse::isButtonPressed(Mouse::Left))
	{
		cout<<Mouse::getPosition(window).x + TrackPosX<<' '<<Mouse::getPosition(window).y + TrackPosY<<'\n';
	}*/
	//cout << TrackPosX << " " << TrackPosY << "\n";
	Track1Sprite.setPosition(-TrackPosX, -TrackPosY);
	window.draw(Track1Sprite);

}
void GameAssets() //A method that loads all my game assets
{
	Track1Sprite = loadAssets.LoadSpriteFromTexture("Assets/", "Race_Track_1", "png");	
	Track1Sprite.setScale(1, 1);	

	Track2Sprite = loadAssets.LoadSpriteFromTexture("Assets/", "Race_Track_2", "png");
	Track2Sprite.setScale(1, 1);

	InstructionMenu = loadAssets.LoadSpriteFromTexture ("Assets/", "InstructionsMenu", "png");

	ViperSprite = loadAssets.LoadSpriteFromTexture("Assets/", "Viper", "png");
	ViperSprite.setOrigin(127.0/2, 256.0/2);
	ViperSprite.scale(0.8, 0.8);

	AudiSprite = loadAssets.LoadSpriteFromTexture("Assets/", "Audi", "png");
	AudiSprite.setOrigin(116.0/2, 255.0/2);
	AudiSprite.scale(0.8, 0.8);

	VanSprite = loadAssets.LoadSpriteFromTexture("Assets/", "Van", "png");
	VanSprite.setOrigin(138.0/2, 256.0/2);
	VanSprite.scale(0.8, 0.8);

	MustangSprite = loadAssets.LoadSpriteFromTexture("Assets/", "Mustang", "png");
	MustangSprite.setOrigin(109.0/2, 256.0/2);
	MustangSprite.scale(0.8, 0.8);

	PlayButton1 = loadAssets.LoadSpriteFromTexture("Assets/", "Play_Button", "png");
	PlayButton1.setOrigin(84.0/2,46.0/2);
	PlayButton1.setPosition(400, 250);

	ExitButton1 = loadAssets.LoadSpriteFromTexture("Assets/", "Exit_Button", "png");
	ExitButton1.setOrigin(90.0/2, 46.0/2);
	ExitButton1.setPosition(405, 350);
}

int main()
{
	//Local Variables
	Event event;
	
	//Setting the window frame rate limit to 60
	window.setFramerateLimit(60);

	GameAssets(); 
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if(event.type == Event::Closed || event.key.code == Keyboard::Escape) 
			{
				window.close(); //Closes the window if you push the escape key
				break;
			}
			if (event.type == Event::MouseMoved) //Mouse Movement
				{
				MouseCursorLocation = Mouse::getPosition(window);
				}
			else if (event.type == Event::MouseButtonPressed)
				{
				if (event.mouseButton.button == Mouse::Left && CURRENT_SCREEN == GAME_MENU_SCREEN)
					{
					if ((MouseCursorLocation.x > PlayButton1.getPosition().x - PlayButton1.getGlobalBounds().width/2) && (MouseCursorLocation.x < (PlayButton1.getPosition().x + PlayButton1.getGlobalBounds().width/2)) && (MouseCursorLocation.y > PlayButton1.getPosition().y - PlayButton1.getGlobalBounds().height/2) && (MouseCursorLocation.y < (PlayButton1.getPosition().y + PlayButton1.getGlobalBounds().height/2)))
						{
							CURRENT_SCREEN = INSTRUCTIONS_MENU_SCREEN; //Changes the current screen if you click on the play button
							car.CarValues (260, 2150, 0, 0);
							audi.CarValues (400, 1920, 0, 0);
							van.CarValues (260, 1920, 0, 0);
							mustang.CarValues (400, 2150, 0, 0);
						}
					if ((MouseCursorLocation.x > ExitButton1.getPosition().x - ExitButton1.getGlobalBounds().width/2) && (MouseCursorLocation.x < (ExitButton1.getPosition().x + ExitButton1.getGlobalBounds().width/2)) && (MouseCursorLocation.y > ExitButton1.getPosition().y - ExitButton1.getGlobalBounds().height/2) && (MouseCursorLocation.y < (ExitButton1.getPosition().y + ExitButton1.getGlobalBounds().height/2)))
						{
							window.close(); //Closes the window if you click on the exit button
						}
					}
				}
			
		}
window.clear();
	if (CURRENT_SCREEN == GAME_MENU_SCREEN)
		{
			window.draw(loadAssets.LoadSpriteFromTexture("Assets/", "GameScreen", "png"));
			window.draw(PlayButton1);
			window.draw(ExitButton1);
		}
	else if (CURRENT_SCREEN == INSTRUCTIONS_MENU_SCREEN)
		{
			window.draw(InstructionMenu);
				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					CURRENT_SCREEN = LEVEL_1_SCREEN;
					//GameStarted = true;
				}
		}
	else if (CURRENT_SCREEN == LEVEL_1_SCREEN)
		{
			inputs();
			window.draw(Track1Sprite);
			window.draw(VanSprite);
			window.draw(MustangSprite);
			window.draw(AudiSprite);
			window.draw(ViperSprite);
		}
	else if (CURRENT_SCREEN == LEVEL_2_SCREEN)
		{
			window.draw(Track2Sprite);
			window.draw(VanSprite);
			window.draw(MustangSprite);
			window.draw(AudiSprite);
			window.draw(ViperSprite);
		}

window.display();
	}
getchar();
return 0;
}

