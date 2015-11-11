#pragma once

#include "core/Serializable.h"

class Room;

class World
	: public Serializable
{
public:
	World();
	~World();

	Room*	createRoom(const char* name);
	void	destroyRoom(Room*);

	bool serialize(Serializer* serializer) override;

private:
	std::unordered_map<StringHash, Room*>	m_rooms;
};
