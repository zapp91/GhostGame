#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Ghost.h"

using namespace std;

//constructor
Ghost::Ghost()
{
	strGhostName = "";	
	nNumLifePoints = 25;

	// initialize random seed:
	srand(time(NULL));
}


//destructor
Ghost::~Ghost()
{
}


//sets Ghost current room
void Ghost::SetCurrentRoom(Room * r)
{
	CurrentRoom = r;
}


//get the Ghost current room
Room Ghost::getCurrentRoom()
{
	return *CurrentRoom;
}


//sets Ghost name
void Ghost::setGhostName(string strName)
{
	strGhostName = strName;
}


//get Ghost name
string Ghost::getGhostName()
{
	return strGhostName;
}


//returns the num life points
int Ghost::getNumLifePoints()
{
	return nNumLifePoints;
}


//reduces life points by nAmt
void Ghost::ReduceLifePoints(int nAmt)
{
	nNumLifePoints -= nAmt;
}


//ghost moves
void Ghost::GhostMove(User *u, bool *lineFlag)
{
	// Is the Ghost in the same room as user u?
	if (u->getCurrentRoom().getRoomName() == CurrentRoom->getRoomName())
	{
		// If so then the ghost can attack the user
		GhostAttack(u);
		*lineFlag = 1;
	}
	//if not the ghost attempts to move to another room
	else
		GhostChangeRoom(u, lineFlag);
}


//ghost attacks user
void Ghost::GhostAttack(User *u)
{
	//display ghosts attacks the user
	cout << "Ghost " << strGhostName << " attacks you";
	
	//used to determine if the ghost hits the users or not
	int iHitUser;

	// generate random number between 1 and 100:
	iHitUser = rand() % 100 + 1;

	// the ghost has a 30 % chance of hitting the user
	if (iHitUser <= 30)
	{
		//used to determine how hard a ghost hits the user
		int iAmtDamage;

		// generate random number between 1 and 10:
		iAmtDamage = rand() % 10 + 1;

		//Ghost does 1 to 10 life points damage to the user, and displays as much
		cout << " and hits you doing " << iAmtDamage << " points of damage!" << endl;

		//reduces the users life points by how hard the ghost hits
		u->ReduceLifePoints(iAmtDamage);
	}
	//ghost misses the user and displays as such
	else
	{
		cout << " and misses!" << endl;
	}
}


//ghost changes room
void Ghost::GhostChangeRoom(User *u, bool *lineFlag)
{
	//random number between 1 and 4 is chosen
	int d = rand() % 4 + 1;

	//a direction enum class is created
	direction dir;

	//a switch statement refers to the randomly chosen number and picks a direction to be put in the enum class
	switch (d)
	{
		case 1: dir = North;
				break;
		case 2: dir = East;
				break;	
		case 3: dir = South;
				break;
		case 4: dir = West;
	}
	
	//a room class is created
	Room * r;

	//checks to see if the direction chosen is viable, if not the ghost doesn't move
	r = CurrentRoom->MoveRoom(dir);

	//if the direction is viable..
	if (r != NULL)
	{	
		//change the ghosts current room to the viable room chosen and..
		CurrentRoom = r;

		//if the ghosts new room is the same as the users, display that the ghosts moved to the room.
		if (CurrentRoom->getRoomName() == u->getCurrentRoom().getRoomName())
		{
			cout << "Ghost " << getGhostName() << " moves to the " << CurrentRoom->getRoomName() << endl;
			*lineFlag = 1;
		}
	}
}
