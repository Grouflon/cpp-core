#pragma once

#include <SFML/Window.hpp>

class Application
{
public:
	Application();
	virtual ~Application();
	
	bool init(int width, int height, const char* name);
	void shutdown();

	void start();
	void requestStop();

	virtual void onStart();
	virtual void onUpdate(float dt);
	virtual void onStop();

private:
	void _processEvents();

	bool		m_initialized;
	bool		m_running;
	sf::Window	m_window;

	// TODO: more elaborate clock, with time multiplier and child clocks
	sf::Clock	m_clock;
};
