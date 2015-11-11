#include "stdafx.h"
#include "adventure/World.h"

#include "adventure/Room.h"

World::World()
{
}

World::~World()
{
}

Room* World::createRoom(const char* name)
{
	StringHash	nameHash = name;
	Room*		room = nullptr;
	if (m_rooms.find(name) == m_rooms.end())
	{
		room = new Room(name);
		m_rooms[nameHash] = room;
	}
	else
	{
		LOG_ERROR("World::createRoom -> Impossible to create room \"%s\", a room with this name already exists.", name);
	}
	return room;
}

void World::destroyRoom(Room* room)
{
	auto it = m_rooms.find(room->getName());
	if (it != m_rooms.end())
	{
		m_rooms.erase(it);
		delete room;
	}
	else
	{
		LOG_WARNING("World::destroyRoom -> Failed to destroy room \"%s\", room not found.", room->getName());
	}
}

bool World::serialize(Serializer* serializer)
{
	return true;
}