#include "stdafx.h"
#include "core/SystemClock.h"

SystemClock::SystemClock()
	: m_startTime(0u)
	, m_stopTime(0u)
	, m_running(false)
	, m_reset(true)
{
}


SystemClock::~SystemClock()
{
}

void SystemClock::start()
{
	if (!m_running)
	{
		if (m_reset)
		{
			m_startTime = SDL_GetTicks();
			m_reset = false;
		}
		else
		{
			m_startTime += SDL_GetTicks() - m_stopTime;
		}

		m_running = true;
	}
}

void SystemClock::stop()
{
	if (m_running)
	{
		m_stopTime = SDL_GetTicks();
		m_running = false;
	}
}

Time SystemClock::reset()
{
	m_reset = true;
	uint32 time = SDL_GetTicks();
	Time result = time - m_startTime;
	if (m_running)
	{
		m_startTime = time;
	}
	else
	{
		m_reset = true;
	}
	return result;
}

Time SystemClock::getTime() const
{
	if (m_running)
	{
		return SDL_GetTicks() - m_startTime;
	}
	else
	{
		if (!m_reset)
		{
			return m_stopTime - m_startTime;
		}
	}
	return 0u;
}