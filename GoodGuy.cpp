#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "GoodGuy.h"

using namespace std;

//constructor
GoodGuy::GoodGuy()
{
	strGoodGuyName = "";	
	nNumLifePoints = 25;

	// initialize random seed:
	srand(time(NULL));
}


//destructor
GoodGuy::~GoodGuy()
{
}


//sets GoodGuy current room
void GoodGuy::SetCurrentRoom(Room * r)
{
	CurrentRoom = r;
}


//get the GoodGuy current room
Room GoodGuy::getCurrentRoom()
{
	return *CurrentRoom;
}


//sets GoodGuy name
void GoodGuy::setGoodGuyName(string strName)
{
	strGoodGuyName = strName;
}


//get GoodGuy name
string GoodGuy::getGoodGuyName()
{
	return strGoodGuyName;
}


//returns the num life points
int GoodGuy::getNumLifePoints()
{
	return nNumLifePoints;
}


//reduces life points
void GoodGuy::ReduceLifePoints(int nAmt)
{
	nNumLifePoints -= nAmt;
}


//GoodGuy moves
void GoodGuy::GoodGuyMove(Ghost g[], int numGhosts, User *u, bool *lineFlag)
{
	//flag to detect if GoodGuy attacks ghost
	bool attackFlag = 0;

	//loops for each ghost
	for (int i = 0; i < numGhosts; i++)
	{
		//Is the GoodGuy in the same room as a ghost, the ghost is alive, and the GoodGuy hasn't attacked yet, attack the ghost
		if ((g[i].getCurrentRoom().getRoomName() == CurrentRoom->getRoomName()) && (g[i].getNumLifePoints() > 0) && (attackFlag == 0))
		{
			// If so then the GoodGuy will attempt to attack the ghost and change the attack flag to true
			GoodGuyAttack(&(g[i]), u, lineFlag);
			attackFlag = 1;
		}
	}

	//if GoodGuy isn't in the same room as a living ghost then they attempt to move to another room
	if (attackFlag == 0)
		GoodGuyChangeRoom(u, lineFlag);
}


//GoodGuy attacks ghost
void GoodGuy::GoodGuyAttack(Ghost *g, User *u, bool *lineFlag)
{
	//value used to determine if a GoodGuy hits a ghost or not
	int iHitGhost;
	
	//explains that a GoodGuy is attacking a ghost if that GoodGuy and you are in the same room
	if (CurrentRoom->getRoomName() == u->getCurrentRoom().getRoomName())
	{
		cout << "Good guy " << getGoodGuyName() << " attacks ghost " << g->getGhostName();
		*lineFlag = 1;	//adds an extra space if a GoodGuy attacks a ghost
	}


	// generate random number between 1 and 100:
	iHitGhost = rand() % 100 + 1;
	//The GoodGuy has a 30 % chance of hitting the ghost
	if (iHitGhost <= 30)
	{
		//used to determine how hard a GoodGuy hits a ghosts
		int iAmtDamage;

		//generates random number between 1 and 10:
		iAmtDamage = rand() % 10 + 1;

		//if the user is in the same room as the GoodGuy attacking the ghost, display what happens
		if (CurrentRoom->getRoomName() == u->getCurrentRoom().getRoomName())
			cout << " hitting them doing " << iAmtDamage << " points of damage!" << endl;
		
		//reduce the ghost's life points by the amount of damage generated
		g->ReduceLifePoints(iAmtDamage);
	}
	//if the GoodGuy misses..
	else
	{	//and the user is in the same room as the GoodGuy, display as such
		if (CurrentRoom->getRoomName() == u->getCurrentRoom().getRoomName())
			cout << " and misses them!" << endl;
	}
}


//GoodGuy changes room
void GoodGuy::GoodGuyChangeRoom(User *u, bool *lineFlag)
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

	//checks to see if the direction chosen is viable
	r = CurrentRoom->MoveRoom(dir);

	//if the direction is available the GoodGuy moves
	if (r != NULL)
	{
		//if the good guys current room is the same as the users room, but their updated room is not, display the GoodGuy left the room
		if ((CurrentRoom->getRoomName() == u->getCurrentRoom().getRoomName()) && (r->getRoomName() != u->getCurrentRoom().getRoomName()))
		{
			cout << "Good guy " << getGoodGuyName() << " leaves the " << CurrentRoom->getRoomName() << endl;
			*lineFlag = 1;
		}

		//updates the GoodGuys room info
		CurrentRoom = r;

		//if the updated room is the same as the users, display the GoodGuy moved into the room
		if (CurrentRoom->getRoomName() == u->getCurrentRoom().getRoomName())
		{
			cout << "Good guy " << getGoodGuyName() << " moves to the " << CurrentRoom->getRoomName() << endl;
			*lineFlag = 1;
		}
	}
	//if the direction is not available the GoodGuy stays in the room
	else if (CurrentRoom->getRoomName() == u->getCurrentRoom().getRoomName())
	{
		cout << "Good guy " << getGoodGuyName() << " stays in the " << CurrentRoom->getRoomName() << endl;
		*lineFlag = 1;
	}
}
