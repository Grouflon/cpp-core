#pragma once
class Time
{
public:
	Time(double seconds);
	Time(const Time& rhs);
	~Time();

	float		asSeconds() const;
	float		asMilliseconds() const;
	std::string	asString() const;

	Time operator+(const Time& rhs) const;
	Time operator-(const Time& rhs) const;
	Time& operator=(const Time& rhs);
	Time& operator+=(const Time& rhs);
	Time& operator-=(const Time& rhs);

private:
	double m_time;
};

