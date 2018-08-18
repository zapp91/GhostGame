#include "string"

#ifndef Room_h
#define Room_h

using namespace std;	//Why is this need here and not in any other header file?

// these are the valid directions that a room can have
enum direction
{
	North,
	South,
	East,
	West
};

// this class is the Room object
class Room
{
private:
	string strRoomName;		//the name of a room
	string strRoomDesc;		//the description of a room
	Room *movementRoom[4];	//the rooms connected to a room
	bool painKillers;		//does the room have painkillers
	bool flashlight;		//does the room have a flashlight
	

public:
	//constuctor
	Room();
	//destructor
	~Room();
	
	//get room name
	string getRoomName();
	//set room name
	void setRoomName(string strName);

	//get room description
	string getRoomDesc();
	//set room description
	void setRoomDesc(string strDesc);

	//set pain killers
	void Room::setPainKillers(bool p);
	//get pain killers
	bool Room::getPainKillers();

	//set flashlight
	void Room::setFlashlight(bool f);
	//get flashlight
	bool Room::getFlashlight();

	//Displays information about a room
	void DisplayRoomInfo();

	//Set room North
	void SetRoomNorth(Room * r);
	//Set room South
	void SetRoomSouth(Room * r);
	//Set room East
	void SetRoomEast(Room * r);
	//Set room West
	void SetRoomWest(Room * r);

	// this will either return null if this is an invalid movement
	// or a pointer to the new room
	Room * MoveRoom(direction d);
};

#endif