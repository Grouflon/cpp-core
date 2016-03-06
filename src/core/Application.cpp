#include "stdafx.h"
#include "core/Application.h"

#include <cstdio>
#include <GL/gl3w.h>
#include <imgui.h>
#include <imgui_impl_sdl_gl3.h>

#include "core/Log.h"
#include "core/Assert.h"
#include "core/ResourceManager.h"


Application::Application()
	: m_initialized(false)
	, m_running(false)
	, m_window(nullptr)
	, m_glContext(nullptr)
	, m_previousTime(0u)
{
}

Application::~Application()
{
}

bool Application::init(int width, int height, const char* name)
{
	if (!m_initialized)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			LOG_ERROR("Failed to initialize SDL: %s.", SDL_GetError());
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (!m_window)
		{
			LOG_ERROR("Failed to create SDL Window: %s", SDL_GetError());
			SDL_Quit();
			return false;
		}

		m_glContext = SDL_GL_CreateContext(m_window);
		if (!m_glContext)
		{
			LOG_ERROR("Failed to create GL Context: %s", SDL_GetError());
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			m_window = nullptr;
			return false;
		}

		if (gl3wInit() == -1 || !ImGui_ImplSdlGL3_Init(m_window))
		{
			LOG_ERROR("Faile to initialize gl3w.");
			SDL_GL_DeleteContext(m_glContext);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			m_window = nullptr;
			m_glContext = nullptr;
			return false;
		}

		// REGISTER TO SERVICE LOCATOR
		ASSERT(Locator::Get<Application>() == nullptr);
		Locator::Register(this);

		m_initialized = true;
	}
	else
	{
		ASSERT(false) // Should not call init two times in a row
		shutdown();
		return init(width, height, name);
	}

	return true;
}

void Application::shutdown()
{
	if (m_initialized)
	{
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		m_window = nullptr;
		m_glContext = nullptr;
	}
	else
	{
		ASSERT(false) // Should not call shutdown two times in a row
	}
}

void Application::start()
{
	ASSERT(m_initialized); // Should not call start before init

	m_systemClock.start();
	m_previousTime = m_systemClock.getTime();

	started();

	m_running = true;
	while(m_running)
	{
		// GAME LOOP
		_updateTime();
		_processEvents();
		_update();
		_render();

		g_resourceManager.flushResources();
	}

	m_systemClock.stop();
	stopped();
}

void Application::requestStop()
{
	m_running = false;
}

void Application::started()
{
}

void Application::render()
{
}

void Application::update(float)
{
}

void Application::stopped()
{
}

glm::ivec2 Application::getWindowSize() const
{
	glm::ivec2 size;
	SDL_GetWindowSize(m_window, &size[0], &size[1]);
	return size;
}

float Application::getWindowRatio() const
{
	glm::ivec2 size = getWindowSize();
	return static_cast<float>(size.x) / static_cast<float>(size.y);
}

Clock& Application::getMainClock()
{
	return m_clock;
}

void Application::_processEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSdlGL3_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
		{
			requestStop();
		}
	}
}

void Application::_updateTime()
{
	Time time = m_clock.getTime();
	Time deltaTime = time - m_previousTime;
	m_clock.update(deltaTime);
	m_previousTime = time;
}

void Application::_update()
{
	ImGui_ImplSdlGL3_NewFrame();
	update(static_cast<float>(m_clock.getElapsedTime().asSeconds()));
}

void Application::_render()
{
	render();
	ImGui::Render();
	SDL_GL_SwapWindow(m_window);
}
