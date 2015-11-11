#pragma once

class Room
{
public:
	Room(const char* name);
	~Room();

	const char* getName() const;

private:
	std::string	m_name;
};
