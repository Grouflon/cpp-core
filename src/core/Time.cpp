#include "stdafx.h"
#include "Time.h"


Time::Time(double seconds)
	: m_time(seconds)
{
}

Time::Time(const Time& rhs)
{
	m_time = rhs.m_time;
}

Time::~Time(void)
{
}

float Time::asSeconds() const
{
	return static_cast<float>(m_time);
}

float Time::asMilliseconds() const
{
	return static_cast<float>(m_time * 1000.0);
}

std::string Time::asString() const
{
	unsigned int time = static_cast<unsigned int>(m_time);
	unsigned int seconds = time % 60u;
	unsigned int minutes = ((time - seconds) % 3600u) / 60u;
	unsigned int hours = (time - minutes - seconds) / 3600u;
	char buffer[16];
	sprintf(buffer, "%02d:%02d:%02d\0", hours, minutes, seconds);
	return std::string(buffer);
}

Time Time::operator+(const Time& rhs) const
{
	return m_time + rhs.m_time;
}

Time Time::operator-(const Time& rhs) const
{
	return m_time - rhs.m_time;
}

Time& Time::operator=(const Time& rhs)
{
	m_time = rhs.m_time;
	return *this;
}

Time& Time::operator+=(const Time& rhs)
{
	m_time += rhs.m_time;
	return *this;
}

Time& Time::operator-=(const Time& rhs)
{
	m_time -= rhs.m_time;
	return *this;
}