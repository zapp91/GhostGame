// GameProj.cpp : Defines the entry point for the console application.
// Edited By Royce Duncan 11/30/17
#include "stdafx.h"
#include <iostream>
#include "Room.h"
#include "User.h"
#include "Ghost.h"
#include "GoodGuy.h"

using namespace std;


//User
	User Player1 = User();
	//function that initializes user
	void setUpUser();


//rooms
	const int numRooms = 9;
	Room Rooms[numRooms] = { Room(), Room(), Room(), Room(), Room(), Room(), Room(), Room(), Room() };
	//function that initializes rooms
	void setUpRooms();


//Ghosts
	const int numGhosts = 5;
	Ghost Ghosts[numGhosts] = { Ghost(), Ghost(), Ghost(), Ghost(), Ghost() };
	//function that initializes Ghosts
	void setUpGhost();


//GoodGuys
	const int numGoodGuy = 3;
	GoodGuy GoodGuys[numGoodGuy] = { GoodGuy(), GoodGuy(), GoodGuy() };
	//function that initializes GoodGuys
	void setUpGoodGuy();


//Prototypes
	//displays a greeting with a list of the games controls
	void DisplayGreeting();
	//displays the ghosts and good guys in the users current room
	void DisplayRoomOccupants(User *u, Ghost g[], GoodGuy guy[]);
	//absorbs health from a good guy
	void SacrificeGoodGuy(User *u, GoodGuy guy[]);
	//attacks a ghost and reduced their health
	void AttackGhost(User *u, Ghost ghosts[]);

int main()
{

	//displays welcome
	DisplayGreeting();

	//set up rooms
	setUpRooms();

	//set up user
	setUpUser();

	//clears the screen after the player initializes their character
	system("CLS");

	//set up Ghosts
	setUpGhost();

	//set up GoodGuys
	setUpGoodGuy();

	//initializes format flag, used for adding extra spaces of their are any GoodGuy or Ghost lines shown
	bool lineFlag = 0;

	//used to either sacrifice a good guy or attack a ghost, this is used for roundabout choice selection
	int userChoice = 0;

	// keep playing until user decides to quit or user dies (i.e., nNumLifePoints <= 0)
	while (!Player1.getUserQuit() && Player1.getNumLifePoints() > 0)
	{

		//resets format flag
		lineFlag = 0;

		//display info current room
		Player1.getCurrentRoom().DisplayRoomInfo();

		//displays the ghosts and good guys in the users current room
		DisplayRoomOccupants(&Player1, Ghosts, GoodGuys);

		//Player 1 move
		userChoice = Player1.UserMove();

		if (userChoice == 1)
			SacrificeGoodGuy(&Player1, GoodGuys);	//roundabout choice, sacrifices a good guy
		else if (userChoice == 2)
			AttackGhost(&Player1, Ghosts);			//roundabout choice, attack a ghost

		//if the user didn't quit, continue the game
		if (!Player1.getUserQuit())
		{

			//allow GoodGuys to move
			for (int i = 0; i < numGoodGuy; i++)
			{
				//is the GoodGuy still alive?
				if (GoodGuys[i].getNumLifePoints() > 0)
				{
					//if so, move or attack the ghost
					GoodGuys[i].GoodGuyMove(Ghosts, numGhosts, &Player1, &lineFlag);
				}
			}

			//adds a space if their are any GoodGuy lines
			if (lineFlag == 1)
			{
				cout << endl;
				lineFlag = 0;
			}

			//allow ghosts to move
			for (int i = 0; i < numGhosts; i++)
			{
				//is the ghost still alive?
				if (Ghosts[i].getNumLifePoints() > 0)
				{
					//if so, move or attack the player
					Ghosts[i].GhostMove(&Player1, &lineFlag);
				}
			}

			//adds a space if their are any ghost lines
			if (lineFlag == 1)
			{
				cout << endl;
				lineFlag = 0;
			}

			cout << "Press enter to continue";

			//waits for the user to press enter
			cin.ignore();
			cin.get();

		}

		//clears the screen after player move
		system("CLS");
	}

	//if the user lost all of their life points, display that they have died
	if (Player1.getNumLifePoints() <= 0)
	{
		cout << "You have died.\n";
	}

	cout << "Thank you for playing!";

	//waits for the user to press enter before closing the game
	cin.ignore();
	cin.get();
	return 0;
}


//function that initializes user
void setUpUser()
{
	//prompt player for name
	string strName;
	cout << "What is your name? ";
	cin >> strName;
	
	//changes the user name to what the player entered
	Player1.setUserName(strName);

	// user starts in the hallway
	Player1.SetCurrentRoom(&Rooms[0]);
}


//function that initializes rooms
void setUpRooms()
{
	// initialize Rooms

	//Bedroom
	Rooms[0].setRoomName("Bedroom");
	Rooms[0].setRoomDesc("You feel a chill come over you. The window is locked.");
	//Hallway
	Rooms[1].setRoomName("Hallway");
	Rooms[1].setRoomDesc("You hear strange noises in all directions. You feel disoriented.");
	//Bathroom
	Rooms[2].setRoomName("Bathroom");
	Rooms[2].setRoomDesc("The room is dark and unsettling. You hear the sink dripping water.");
	Rooms[2].setPainKillers(1);	//this room has painkillers
	//Guest Room
	Rooms[3].setRoomName("Guest Room");
	Rooms[3].setRoomDesc("You have the sudden urge to run. The air is thick and hard to breath.");
	//Kitchen
	Rooms[4].setRoomName("Kitchen");
	Rooms[4].setRoomDesc("The sink light is flickering quickly. You hear a loud noise comming from the living room.");
	//Living Room
	Rooms[5].setRoomName("Living Room");
	Rooms[5].setRoomDesc("Everything becomes disturbingly quiet. You feel eyes watching you.");
	//Front Yard
	Rooms[6].setRoomName("Garage");
	Rooms[6].setRoomDesc("The fluorescent light is buzzing loudly. You see clutter on the couters.");
	Rooms[6].setFlashlight(1);	//this room has a flashlight
	//Backyard
	Rooms[7].setRoomName("Backyard");
	Rooms[7].setRoomDesc("You hear a growl in the distance. The sound of rustling bushes gets closer.");
	//Treehouse
	Rooms[8].setRoomName("Treehouse");
	Rooms[8].setRoomDesc("The sound of wind and branches becomes louder. You hear the wooden boards bend and creak.");

	//Set up movement
	//One Door
		//The bedroom is to the south of the hallway
		Rooms[1].SetRoomSouth(&Rooms[0]);
		//The hallway is to the north of the bedroom
		Rooms[0].SetRoomNorth(&Rooms[1]);
	//Two Door
		//The bathroom is to the east of the hallway
		Rooms[1].SetRoomEast(&Rooms[2]);
		//The hallway is to the west of the bathroom
		Rooms[2].SetRoomWest(&Rooms[1]);
	//Three Door
		//The hallway is to the south of the guest room
		Rooms[3].SetRoomSouth(&Rooms[1]);
		//The guest room is to the north of the hallway
		Rooms[1].SetRoomNorth(&Rooms[3]);
	//Fourth Door
		//The hallway is to the east of the kitchen
		Rooms[4].SetRoomEast(&Rooms[1]);
		//The kitchen is to the west of the hallway
		Rooms[1].SetRoomWest(&Rooms[4]);
	//Fifth Door
		//The livingRoom is to the south of the kitchen
		Rooms[4].SetRoomSouth(&Rooms[5]);
		//The kitchen is to the north of the living room
		Rooms[5].SetRoomNorth(&Rooms[4]);
	//Sixth Door
		//The living room is to the east of the garage
		Rooms[6].SetRoomEast(&Rooms[5]);
		//The garage is to the west of the living room
		Rooms[5].SetRoomWest(&Rooms[6]);
	//Seventh Door
		//The garage is to the south of the backyard
		Rooms[7].SetRoomSouth(&Rooms[6]);
		//The backyard is to the north of the garage
		Rooms[6].SetRoomNorth(&Rooms[7]);
	//Eighth Door
		//The backyard is to the south of the treehouse
		Rooms[8].SetRoomSouth(&Rooms[7]);
		//The treehouse is to the north of the backyard
		Rooms[7].SetRoomNorth(&Rooms[8]);
	//Tenth Door
		//The kitchen is to the east of the backyard
		Rooms[7].SetRoomEast(&Rooms[4]);
		//The backyard is to the west of the kitchen
		Rooms[4].SetRoomWest(&Rooms[7]);
}


//function that initializes ghost
void setUpGhost()
{
	//Set up Tina the Ghost
	Ghosts[0].setGhostName("Tina");
	// Tina starts in the bedroom
	Ghosts[0].SetCurrentRoom(&Rooms[8]);

	//Set up Mike the Ghost
	Ghosts[1].setGhostName("Mike");
	// Mike starts in the hallway
	Ghosts[1].SetCurrentRoom(&Rooms[1]);

	//Set up Emma the Ghost
	Ghosts[2].setGhostName("Emma");
	// Emma starts in the kitchen
	Ghosts[2].SetCurrentRoom(&Rooms[4]);

	//Set up Erik the Ghost
	Ghosts[3].setGhostName("Erik");
	// Erik starts in the living room
	Ghosts[3].SetCurrentRoom(&Rooms[5]);

	//Set up Carl the Ghost
	Ghosts[4].setGhostName("Carl");
	// Carl starts in the guest room
	Ghosts[4].SetCurrentRoom(&Rooms[3]);
}


//function that initializes good guys
void setUpGoodGuy()
{
	//Set up April the GoodGuy
	GoodGuys[0].setGoodGuyName("April");
	//April starts in the backyard
	GoodGuys[0].SetCurrentRoom(&Rooms[7]);

	//Set up Steve the GoodGuy
	GoodGuys[1].setGoodGuyName("Steve");
	//Steve starts in the bathroom
	GoodGuys[1].SetCurrentRoom(&Rooms[2]);

	//Set up Aaron the GoodGuy
	GoodGuys[2].setGoodGuyName("Aaron");
	//Aaron starts in the kitchen
	GoodGuys[2].SetCurrentRoom(&Rooms[4]);
}


//displays welcome screen
void DisplayGreeting()
{
	cout << "Welcome to the Ghost Game!" << endl;
	cout << "In this game there are rooms, painkillers, good guys, and ghosts!" << endl << endl;
	Player1.DisplayHelp();	//uses help list in the greeting
}


//displays the ghosts and good guys in the users current room
void DisplayRoomOccupants(User *u, Ghost g[], GoodGuy guy[])
{
	//flags used for line spacing
	bool a = 0, b = 0;

	//loops for every good guy
	for (int i = 0; i < numGoodGuy; i++)
	{
		//if the player and the good guy are in the same room display that you see them either alive or dead
		if (u->getCurrentRoom().getRoomName() == guy[i].getCurrentRoom().getRoomName())
		{
			cout << "You see good guy " << guy[i].getGoodGuyName();
			if (guy[i].getNumLifePoints() > 0)
				cout << " alive." << endl;
			else
				cout << " dead." << endl;

			a = 1;
		}
	}

	//if the user sees a good guy add an extra line for spacing
	if (a == 1)
		cout << endl;

	//loop for every ghost
	for (int i = 0; i < numGhosts; i++)
	{
		//if the player and the ghost are in the same room display that you see them alive or dead
		if (u->getCurrentRoom().getRoomName() == g[i].getCurrentRoom().getRoomName())
		{
			cout << "You see ghost " << g[i].getGhostName();
			if (g[i].getNumLifePoints() > 0)
				cout << " alive." << endl;
			else
				cout << " dead." << endl;

			b = 1;
		}
	}

	//if the user sees a ghost add an extra line for spacing
	if (b == 1)
		cout << endl;
}



//absorbs health from a good guy
void SacrificeGoodGuy(User *u, GoodGuy guy[])
{
	//used to determine if the player has already sacrificed a good guy this turn
	bool sacrificeFlag = 0;

	//loops for every good guy
	for (int i = 0; i < numGoodGuy; i++)
	{
		//if the GoodGuy in the same room as the player, are still alive, and the user hasn't sacrificed anyone yet.
		if ((guy[i].getCurrentRoom().getRoomName() == u->getCurrentRoom().getRoomName()) && (guy[i].getNumLifePoints() > 0) && sacrificeFlag == 0)
		{
			guy[i].ReduceLifePoints(25);
			u->AddLifePoints(25);
			sacrificeFlag = 1;
			//if the good guy is still alive display this messege
			if (guy[i].getNumLifePoints() > 0)
				cout << "You absorbed life from good guy " << guy[i].getGoodGuyName() << "!" << endl << endl;
			//if the good guy is not alive any more display this messege
			else
				cout << "You absorbed life from and sacrificed good guy " << guy[i].getGoodGuyName() << "!" << endl << endl;
		}
	}
}


//attacks a ghost and reduced their health
void AttackGhost(User *u, Ghost ghosts[])
{
	//a flag used to determine if a user has already attacked or no
	bool attackFlag = 0;

	//loops for every ghost
	for (int i = 0; i < numGhosts; i++)
	{
		//if the ghost in the same room as the player, are still alive, and the user hasn't attacked yet.
		if ((ghosts[i].getCurrentRoom().getRoomName() == u->getCurrentRoom().getRoomName()) && (ghosts[i].getNumLifePoints() > 0) && attackFlag == 0)
		{
			//if the player has a flashlight attack the ghost and display as such
			if (u->getFlashlight() == 1)
			{
				ghosts[i].ReduceLifePoints(25);
				u->AddLifePoints(25);
				attackFlag = 1;
				cout << "You attacked ghost " << ghosts[i].getGhostName() << " with a flashlight";
				
				//if the ghosts life points are reduced to or below zero, display the ghost has died
				if (ghosts[i].getNumLifePoints() <= 0)
					cout << ", killing them!";
				//if not, finish the sentence
				else
					cout << "!";
					
				cout << endl << endl;
			}
			//if the player doesn't have a flashlight do not attack and display a messege why
			else if (u->getFlashlight() == 0)
			{
				cout << "You do not have anything to attack with!" << endl << endl;
				attackFlag = 1;
			}
		}
	}
}