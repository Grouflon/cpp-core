#include "stdafx.h"
#include "adventure/Room.h"

Room::Room(const char* name)
	: m_name(name)
{
}

Room::~Room()
{
}

const char* Room::getName() const
{
	return m_name.c_str();
}