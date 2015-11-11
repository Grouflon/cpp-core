#include "stdafx.h"
#include "Clock.h"


Clock::Clock()
	: m_startTime(0.0)
	, m_stopTime(0.0)
	, m_running(false)
	, m_reset(true)
{
}


Clock::~Clock()
{
}

void Clock::start()
{
	if (!m_running)
	{
		if (m_reset)
		{
			m_startTime = glfwGetTime();
			m_reset = false;
		}
		else
		{
			m_startTime += glfwGetTime() - m_stopTime;
		}

		m_running = true;
	}
}

void Clock::stop()
{
	if (m_running)
	{
		m_stopTime = glfwGetTime();
		m_running = false;
	}
}

Time Clock::reset()
{
	m_reset = true;
	double time = glfwGetTime();
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

Time Clock::getTime() const
{
	if (m_running)
	{
		return glfwGetTime() - m_startTime;
	}
	else
	{
		if (!m_reset)
		{
			return m_stopTime - m_startTime;
		}
	}
	return 0.0;
}