#include "stdafx.h"
#include "core/Clock.h"

Clock::Clock()
	: m_timeRatio(1.f)
	, m_time(0u)
	, m_realTime(0u)
{
}

Clock::~Clock()
{
}

void Clock::update(Time _dt)
{
	m_realElapsedTime = _dt;
	m_elapsedTime = static_cast<uint32>(static_cast<float>(_dt.asMilliseconds()) * m_timeRatio);
	m_realTime += m_realElapsedTime;
	m_time += m_elapsedTime;

	for (auto clock : m_children)
	{
		clock->update(m_elapsedTime);
	}
}

void Clock::reset()
{
	m_realTime = 0u;
	m_time = 0u;
}

Time Clock::getTime() const
{
	return m_time;
}

Time Clock::getRealTime() const
{
	return m_realTime;
}

Time Clock::getElapsedTime() const
{
	return m_elapsedTime;
}

Time Clock::getRealElapsedTime() const
{
	return m_realElapsedTime;
}

void Clock::setTimeRatio(float _value)
{
	m_timeRatio = _value;
}

float Clock::getTimeRatio() const
{
	return m_timeRatio;
}

void Clock::addChild(Clock* _clock)
{
#ifdef _DEBUG
	ASSERT(std::find(m_children.begin(), m_children.end(), _clock) == m_children.end());
#endif
	m_children.push_back(_clock);
	_clock->loadUse();
}

void Clock::removeChild(Clock* _clock)
{
	auto it = std::find(m_children.begin(), m_children.end(), _clock);
	if (it != m_children.end())
	{
		m_children.erase(it);
		_clock->releaseUnuse();
	}
}