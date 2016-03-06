#pragma once

#include "core/Time.h"

class SystemClock
{
public:
	SystemClock();
	~SystemClock();

	void start();
	void stop();
	Time reset();

	Time getTime() const;

private:
	uint32	m_startTime;
	uint32  m_stopTime;
	bool	m_running;
	bool	m_reset;
};

