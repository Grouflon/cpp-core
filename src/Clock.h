#pragma once

#include "core/Time.h"

class Clock
{
public:
	Clock();
	~Clock();

	void start();
	void stop();
	Time reset();

	Time getTime() const;

private:
	double	m_startTime;
	double	m_stopTime;
	bool	m_running;
	bool	m_reset;
};

