#pragma once

class Serializer;

class Serializable
{
public:

	Serializable() {}
	virtual ~Serializable() {}

	virtual bool serialize(Serializer* serializer) = 0;
};
