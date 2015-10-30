#pragma once

//#include <SFML/Window.hpp>

class Application
{
public:
	Application();
	virtual ~Application();
	
	bool init(int width, int height, const char* name);
	void shutdown();

	void start();
	void requestStop();

	virtual void started();
	virtual void update(float dt);
	virtual void render();
	virtual void stopped();

private:
	void _processEvents();
	void _update();
	void _render();
	void _glfw_errorCallback(int error, const char* descritpion);
	void _glfw_windowCloseCallback(GLFWwindow* window);

	bool		m_initialized;
	GLFWwindow* m_window;
	double		m_previousTime;
	//sf::Window	m_window;

	// TODO: more elaborate clock, with time multiplier and child clocks
	//sf::Clock	m_clock;
};
