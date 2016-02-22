#include "stdafx.h"
#include "core/Time.h"


Time::Time(uint32 _milliseconds)
	: m_time(_milliseconds)
{
}

Time::Time(const Time& rhs)
{
	m_time = rhs.m_time;
}

Time::~Time(void)
{
}

double Time::asSeconds() const
{
	return static_cast<double>(m_time) / 1000.0;
}

uint32 Time::asMilliseconds() const
{
	return m_time;
}

std::string Time::asString() const
{
	unsigned int time = static_cast<unsigned int>(m_time / 1000);
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