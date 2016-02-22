#pragma once

#include <glm/glm.hpp>

#include "core/Clock.h"

struct SDL_Window;
typedef void* SDL_GLContext;

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

	glm::ivec2	getWindowSize() const;
	float		getWindowRatio() const;

	const Clock&	getClock() const;

private:
	void _processEvents();
	void _update();
	void _render();

	bool		m_initialized;
	bool		m_running;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	double		m_previousTime;
	Clock		m_clock;
};
