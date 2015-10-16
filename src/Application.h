#pragma once

#include "SFML/Window.hpp"

class Application
{
public:
	Application();
	~Application();
	
	void init(int width, int height, const char* name);
	void shutdown();

	void start();
	void requestStop();

private:
	bool		m_initialized;
	bool		m_running;
	sf::Window	m_window;
};
