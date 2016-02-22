#pragma once

#include <string>

class Time
{
public:
	Time(uint32 _milliseconds);
	Time(const Time& rhs);
	~Time();

	double		asSeconds() const;
	uint32		asMilliseconds() const;
	std::string	asString() const;

	Time operator+(const Time& rhs) const;
	Time operator-(const Time& rhs) const;
	Time& operator=(const Time& rhs);
	Time& operator+=(const Time& rhs);
	Time& operator-=(const Time& rhs);

private:
	uint32 m_time;
};

