#include "string"

#ifndef GoodGuy_h
#define GoodGuy_h

#include "Room.h"
#include "Ghost.h"
#include "User.h"

class GoodGuy
{
private:
	string strGoodGuyName;	//GoodGuys name
	int nNumLifePoints;		//GoodGuys life points
	Room *CurrentRoom;		//GoodGuys current room

public:
	//constructor
	GoodGuy();
	//destructor
	~GoodGuy();

	//set name of GoodGuy
	void setGoodGuyName(string strName);
	//get GoodGuy name
	string getGoodGuyName();

	//set GoodGuy Current Room
	void SetCurrentRoom(Room * r);
	//get the GoodGuy current room
	Room getCurrentRoom();

	//returns the num life points
	int getNumLifePoints();
	//reduces life points
	void ReduceLifePoints(int nAmt);

	//GoodGuy moves
	void GoodGuyMove(Ghost g[], int numGhosts, User *u, bool *lineFlag);

	//GoodGuy attacks ghost
	void GoodGuyAttack(Ghost *g, User *u, bool *lineFlag);

	//GoodGuy changes room
	void GoodGuyChangeRoom(User *u, bool *lineFlag);
};

#endif