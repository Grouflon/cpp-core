#pragma once

#include "core/Resource.h"
#include "core/Time.h"

class Clock
	: public Resource
{
public:
	Clock();
	virtual ~Clock();

	void update(Time _dt);
	void reset();

	Time getTime() const;
	Time getRealTime() const;
	Time getElapsedTime() const;
	Time getRealElapsedTime() const;

	void setTimeRatio(float _value);
	float getTimeRatio() const;

	void addChild(Clock* _clock);
	void removeChild(Clock* _clock);

private:
	float m_timeRatio;
	Time m_time;
	Time m_realTime;
	Time m_elapsedTime;
	Time m_realElapsedTime;

	std::vector<Clock*> m_children;
};

