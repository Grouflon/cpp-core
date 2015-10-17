#pragma once

class Serializer;

class Serializable
{
public:

	Serializable() {}
	virtual ~Serializable() {}

	virtual void serialize(Serializer* serializer) = 0;
};
