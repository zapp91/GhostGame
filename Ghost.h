#include "string"
#include "GoodGuy.h"	//If I can include GoodGuy.h then I can create an AttackGoodGuy function

#ifndef Ghost_h
#define Ghost_h

#include "Room.h"
#include "User.h"

class Ghost
{
private:
	string strGhostName;	//a ghosts name
	int nNumLifePoints;		//a ghosts life points
	Room *CurrentRoom;		//a ghosts currents

public:
	//constructor
	Ghost();
	//destructor
	~Ghost();

	//set name of Ghost
	void setGhostName(string strName);
	//get Ghost name
	string getGhostName();

	//set Ghost Current Room
	void SetCurrentRoom(Room * r);
	//get the Ghost current room
	Room getCurrentRoom();

	//returns the num life points
	int getNumLifePoints();
	//reduces life points
	void ReduceLifePoints(int nAmt);

	//ghost moves
	void GhostMove(User *u, bool *lineFlag);

	//ghost attacks player
	void GhostAttack(User *u);

	//ghost changes room
	void GhostChangeRoom(User *u, bool *lineFlag);
};
#endif