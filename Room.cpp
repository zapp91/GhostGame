#include "stdafx.h"
#include <iostream>
#include "Room.h"

using namespace std;

//constructor
Room::Room()
{
	strRoomName = "";	
	strRoomDesc = "";
	painKillers = 0;
	flashlight = 0;

	movementRoom[North] = NULL;	
	movementRoom[South] = NULL;
	movementRoom[East] = NULL;
	movementRoom[West] = NULL;
}


//destructor
Room::~Room()
{
}


//get room name
string Room::getRoomName()
{
	return strRoomName;
}


//set room name
void Room::setRoomName(string strName)
{
	strRoomName = strName;
}


//get room description
string Room::getRoomDesc()
{
	return strRoomDesc;
}


//set pain killers in a room
void Room::setPainKillers(bool p)
{
	painKillers = p;
}


//get pain killers
bool Room::getPainKillers()
{
	return painKillers;
}


//set flashlight in a room
void Room::setFlashlight(bool f)
{
	flashlight = f;
}


//get flashlight
bool Room::getFlashlight()
{
	return flashlight;
}


//set room description
void Room::setRoomDesc(string strDesc)
{
	strRoomDesc = strDesc;
}


//Displays the room name and description
void Room::DisplayRoomInfo()
{
	//displays where the player is and the rooms discription
	cout << "You are in the " << strRoomName << endl;
	cout << strRoomDesc << endl << endl;

	//displays if the room has painkillers
	if (painKillers == 1)
		cout << "You see painkillers." << endl << endl;

	//displays if the room has a flashlight
	if (flashlight == 1)
		cout << "You see a flashlight." << endl << endl;

	//if their is a room to the north, east, south, or west, display as such with the room's name
	if (MoveRoom(North) != NULL)
		cout << "The " << MoveRoom(North)->getRoomName() << " is to the north." << endl;
	if (MoveRoom(East) != NULL)
		cout << "The " << MoveRoom(East)->getRoomName() << " is to the east." << endl;
	if (MoveRoom(South) != NULL)
		cout << "The " << MoveRoom(South)->getRoomName() << " is to the south." << endl;
	if (MoveRoom(West) != NULL)
		cout << "The " << MoveRoom(West)->getRoomName() << " is to the west." << endl;

	//used for line spacing
	cout << endl;
}


// Links rooms so that user can move through them
//Set room North
void Room::SetRoomNorth(Room * r)
{
	movementRoom[North] = r;
}


//Set room South
void Room::SetRoomSouth(Room * r)
{
	movementRoom[South] = r;
}


//Set room East
void Room::SetRoomEast(Room * r)
{
	movementRoom[East] = r;
}


//Set room West
void Room::SetRoomWest(Room * r)
{
	movementRoom[West] = r;
}


// this will either return null if this is an invalid movement
// or a pointer to the new room
Room * Room::MoveRoom(direction d)
{
	return movementRoom[d];
}