#include "stdafx.h"
#include <iostream>
#include "User.h"

using namespace std;

//constructor
User::User()
{
	strUserName = "";		
	nNumLifePoints = 100;	
	bool flashlight = 0;
}							


//destructor
User::~User()
{
}


//current room
//sets users current room
void User::SetCurrentRoom(Room * r)
{
	CurrentRoom = r;
}


//get the users current room
Room User::getCurrentRoom()
{
	return *CurrentRoom;
}


//gets user name
string User::getUserName()
{
	return strUserName;
}


//sets user name
void User::setUserName(string strName)
{
	strUserName = strName;
}


//returns the num life points
int User::getNumLifePoints()
{
	return nNumLifePoints;
}


// reduces the life points by nAmt
void User::ReduceLifePoints(int nAmt)
{
	nNumLifePoints -= nAmt;
}


//adds life points to the user by nAmt
void User::AddLifePoints(int nAmt)
{
	nNumLifePoints += nAmt;
}


//uses a rooms painkillers
void User::UsePainKillers()
{
	//if the users current room has painkillers, remove them and add life points to the user, and display as such
	if (CurrentRoom->getPainKillers() == 1)
	{
		nNumLifePoints += 25;
		CurrentRoom->setPainKillers(0);
		cout << "You have used the painkiller.";
		UserDescribeHealth();
	}
	else
		//if the room doesn't have painkillers, display as such
		cout << "There are no painkillers! You lost a turn!" << endl;
}


//allows the users flashlight attribute to be true or false
void User::setFlashlight(bool f)
{
	flashlight = f;
}



//returns if the user has a flashlight or not
bool User:: getFlashlight()
{
	return flashlight;
}



//lets the user attempt to pickup a rooms flashlight
void User::pickupFlashlight()
{
	//if the users current room has a flashlight and the user doesn't already have a flashlight, pick up the flashlight and display as such
	if ((CurrentRoom->getFlashlight() == 1) && (getFlashlight() == 0))
	{
		CurrentRoom->setFlashlight(0);
		setFlashlight(1);
		cout << "You have picked up a flashlight!" << endl << endl;
	}
	//if the user's current room has a flashlight and the user does have one, state that the user already has one
	else if ((CurrentRoom->getFlashlight() == 1) && (getFlashlight() == 1))
		cout << "You already have a flashlight!" << endl << endl;
	//if the user's current room doesn't have a flashlight, display as such
	else if ((CurrentRoom->getFlashlight() == 0))
		cout << "This room doesn't have a flashlight! You have lost a turn!" << endl << endl;
}

//user moves
int User::UserMove()
{
	string strMove;	//used to collect a users input
	int choice = 0;	//used for roundabout choice selection in the main.cpp file
	
	do
	{
		//ask the user what to do
		cout << "What would you like to do, " << getUserName() << "? ";
		cin >> strMove;
		cout << endl;
		
		//displays a list of possible inputs
		if (strMove == "?")	
			DisplayHelp();
		//describes users health
		else if ((strMove == "H") || (strMove == "h"))
			UserDescribeHealth();

	//repeats if the user selected display help or display health
	} while (strMove == "?" || strMove == "H" || strMove == "h");

	//clears the screen for new lines
	system("CLS");

	//validate move
	if ((strMove == "N") || (strMove == "n")) // move north
		UserChangeRoom(North);
	else if ((strMove == "S") || (strMove == "s")) // move south
		UserChangeRoom(South);
	else if ((strMove == "E") || (strMove == "e")) // move east
		UserChangeRoom(East);
	else if ((strMove == "W") || (strMove == "w")) // move west
		UserChangeRoom(West);
	else if ((strMove == "Q") || (strMove == "q")) // user quit
		bUserQuit = true;
	else if ((strMove == "P") || (strMove == "p")) // user quit
		UsePainKillers();
	else if ((strMove == "F") || (strMove == "f")) // user quit
		pickupFlashlight();
	else if ((strMove == "G") || (strMove == "g")) // user sacrifices a good guy
		choice = 1;	//roundabout choice selection
	else if ((strMove == "A") || (strMove == "a")) // user attacks a ghost
		choice = 2;	//roundabout choice selection
	else
		cout << "Invalid command! You lost a turn!" << endl << endl;
	return choice;
}


// user change room
void User::UserChangeRoom(direction d)
{
	//creates a temp room pointer
	Room * r;

	//returns if the direction the user wants to go to has a room or not
	r = CurrentRoom->MoveRoom(d);

	//if the direction doesn't have a room, display as such
	if (r == NULL)
		cout << "You can not move that way! There is no door there!" << endl << endl;

	//if the direction does have a room, move the user into the room and dislay as such
	else
	{
		CurrentRoom = r;
		cout << "You have moved to the " << CurrentRoom->getRoomName() << endl << endl;
	}
}


// describes users health
void User::UserDescribeHealth()
{
	//temp value to store the users current life points value
	int h = getNumLifePoints();

	//displays a description of the users health status depending on the user's number of life points
	if (h > 90)
		cout << "You are in great health." << endl;
	else if (h > 75)
		cout << "You are in good health." << endl;
	else if (h > 50)
		cout << "You are in ok health" << endl;
	else if (h > 25)
		cout << "You are in poor health" << endl;
	else if (h > 1)
		cout << "You are in severe health" << endl;

	cout << endl;
}


//displays the help screen
void User::DisplayHelp()
{
	cout << "Enter N, E, S, or W to move around the game." << endl;
	cout << "Enter H to check your health." << endl;
	cout << "Enter Q to quit the game." << endl;
	cout << "Enter P to use a rooms painkillers." << endl;
	cout << "Enter F to pick up a rooms flashlight." << endl;
	cout << "Enter G to absorb life from a good guy in the room." << endl;
	cout << "Enter A to attack a ghost in the room." << endl;
	cout << "Enter ? to show this list in-game." << endl << endl;
}


//get User Quit
bool User::getUserQuit()
{
	return bUserQuit;
}
