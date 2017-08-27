#pragma once

#include "core/Types.h"
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
	bool	m_running;
	bool	m_reset;
	uint32	m_startTime;
	uint32  m_stopTime;
};

