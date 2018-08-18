#include "string"

#ifndef User_h
#define User_h

#include "Room.h"

class User
{
private:
	string strUserName;			//the user name
	int nNumLifePoints;			//the user's life points
	Room *CurrentRoom;			//the user's current room
	bool flashlight;			//does the user have a flashlight
	bool bUserQuit = false;		//does the user quit

public:
	//constructor
	User();
	//destructor
	~User();

	//gets user name
	string getUserName();
	//sets user name
	void setUserName(string strName);

	//sets the users current room
	void SetCurrentRoom(Room * r);
	//get the users current room
	Room getCurrentRoom();

	//returns the num life points
	int getNumLifePoints();
	//reduces life points
	void ReduceLifePoints(int nAmt);
	//adds life points
	void AddLifePoints(int nAmt);

	//uses a rooms painkillers
	void UsePainKillers();

	//allows the users flashlight attribute to be true or false
	void User::setFlashlight(bool f);

	//returns if the user has a flashlight or not
	bool User::getFlashlight();

	//lets the user attempt to pickup a rooms flashlight
	void User::pickupFlashlight();

	//user moves
	int UserMove();

	// user change room
	void UserChangeRoom(direction d);

	// descibes users health
	void UserDescribeHealth();

	//displays the help screen
	void DisplayHelp();

	//get User Quit
	bool getUserQuit();
};

#endif