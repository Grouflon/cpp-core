#pragma once

#include <string>
#include "core/Types.h"

class Time
{
public:
	Time(u32 _milliseconds = 0u);
	Time(const Time& rhs);
	~Time();

	double		asSeconds() const;
	u32		asMilliseconds() const;
	std::string	asString() const;

	Time operator+(const Time& rhs) const;
	Time operator-(const Time& rhs) const;
	Time& operator=(const Time& rhs);
	Time& operator+=(const Time& rhs);
	Time& operator-=(const Time& rhs);

private:
	u32 m_time;
};

