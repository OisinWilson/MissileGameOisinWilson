//Name: Oisin Wilson
//Login: C00213826
//--------------------------------------
// Command propt text based missile game
//--------------------------------------
//Known bugs:
//No known bugs

#include <iostream>
#include <stdlib.h>
#include <time.h>

//declare functions
bool gameLoop();

// coordinate info
typedef struct Position
{
	int x;
	int y;
	void print()
	{
		std::cout << x << " , " << y << std::endl;
	}
}Coordinates;

// choice of explosion type
enum WarHead{EXPLOSIVE, NUCLEAR};

// enemy class
typedef struct Enemy
{
	Coordinates coordinates;
}Target;

// player class
struct Missile
{
	WarHead payload;
	Coordinates coordinates;
	Target target;

	short int explosionRadius;
	bool armed = false;

	void arm()
	{
		if (armed)
			armed = false;
		else
			armed = true;
	}
};

bool gameLoop()
{
//Create missile, and set random seed
	Missile rocket;
	srand(time(NULL));

//enemy position
	rocket.target.coordinates.x = { rand() % 100 };
	rocket.target.coordinates.y = { rand() % 100 };

	short int amountOfRockets = 5;
	short int const LAUNCH_CODE = 1234;

//game loop
	while (amountOfRockets > 0)
	{
		// set input nums to 0 
		float inputWarHead = 0;
		float inputDistance = 0;
		float inputLaunchCode = 0;

		// player input, choice of warhead
		while (inputWarHead != 1 && inputWarHead != 2)
		{
			std::cout << "Ammunition Remaining : " << amountOfRockets << "\n" << std::endl;
			std::cout << "Choose WarHead Type:" << std::endl << "1) Explosive" << "\t" << "2) Nuclear" << std::endl;
			std::cin >> inputWarHead;
			std::cout << "\n" << std::endl;
		}

		if (inputWarHead == 1)
		{
			rocket.payload = EXPLOSIVE;
			rocket.explosionRadius = 20;
		}
		else if (inputWarHead == 2 && amountOfRockets > 1)
		{
			rocket.payload = NUCLEAR;
			rocket.explosionRadius = 30;
		}
		else if (inputWarHead == 2 && amountOfRockets <= 1)
		{
			std::cout << "Can't afford the Nuke gotta go with Explosives" << "\n" << std::endl;
			rocket.payload = EXPLOSIVE;
			rocket.explosionRadius = 20;
		}

		// aqiring enemy txt
		std::cout << "Target Acquired" << "\n" << std::endl;

		// launch codes
		while (inputLaunchCode != LAUNCH_CODE)
		{
			std::cout << "Please confirm launch code 1234" << std::endl;
			std::cin >> inputLaunchCode;
			std::cout << std::endl;

			if (inputLaunchCode != LAUNCH_CODE)
			{
				std::cout << "Error! Wrong Input" << std::endl;
			}
		}

		// arming missle, sets position of rocket
		while (inputDistance != 1 && inputDistance != 2 && inputDistance != 3)
		{
			std::cout << "Input desired distance to finialise Missile Arming " << std::endl;
			std::cout << "1) Close" << "\t" << "2) Moderate" << "\t" << "3) Far" << std::endl;
			std::cin >> inputDistance;
			std::cout << "\n" << std::endl;
		}

		std::cout << "Missile Armed" << "\n\nLaunched\n" << std::endl;
		rocket.arm();
		rocket.coordinates = { 50, 150 };

		// launch rocket
		while (rocket.armed)
		{
			// rocket movement
			if (inputDistance == 1)
			{
				rocket.coordinates = { rocket.coordinates.x - 3, rocket.coordinates.y - 3 };
			}
			else if (inputDistance == 2)
			{
				rocket.coordinates = { rocket.coordinates.x, rocket.coordinates.y - 1 };
			}
			else if (inputDistance == 3)
			{
				rocket.coordinates = { rocket.coordinates.x + 3, rocket.coordinates.y - 3 };
			}

			// colision check
			if (sqrt(((rocket.target.coordinates.x - rocket.coordinates.x) * (rocket.target.coordinates.x - rocket.coordinates.x))
				+ ((rocket.target.coordinates.y - rocket.coordinates.y) * (rocket.target.coordinates.y - rocket.coordinates.y)))
				<= rocket.explosionRadius)
			{
				std::cout << "Target Destroyed Congratulations You Win!" << "\n" << std::endl;
				return 1;
			}

			// border check
			if (rocket.coordinates.x <= 0 || rocket.coordinates.y <= 0)
			{
				std::cout << "Target Missed!" << std::endl;

				//remove value of missile used from total
				if (rocket.payload == EXPLOSIVE)
				{
					amountOfRockets -= 1;
					rocket.arm();
				}
				else
				{
					amountOfRockets -= 2;
					rocket.arm();
				}

				//asks to replay
				if (amountOfRockets != 0)
				{
					std::cout << "Fire another Missile?" << "\n" << "1) yes\t2) No" << std::endl;
					float playAgain = 0;
					std::cin >> playAgain;
					std::cout << std::endl;

					//quits game
					if (playAgain == 2)
					{
						return 0;
					}
				}
			}
		}
	}
}

int main()
{
	//enters game loop
	if (gameLoop() == 0)
	{
		std::cout << "\n" << "Game Over" << std::endl;
	}
	system("PAUSE");
	return 0;
}