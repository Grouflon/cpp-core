#include "stdafx.h"
#include "core/Application.h"

#include <cstdio>
#include <GL/gl3w.h>
#include <imgui.h>
#include <imgui_impl_sdl_gl3.h>

#include "core/Log.h"
#include "core/Assert.h"
#include "core/ResourceManager.h"

/*
static void glfw_errorCallback(int error, const char* description)
{
	LOG_ERROR("ERROR: GLFW ERROR: code %d msg: %s", error, description);
	ASSERT(false);
}

static void glfw_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->onKeyEvent(key, scancode, action, mods);
}

static void glfw_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);
}

static void glfw_scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
}

static void glfw_charCallback(GLFWwindow* window, unsigned int c)
{
	ImGui_ImplGlfwGL3_CharCallback(window, c);
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->onCharEvent(c);
}*/


Application::Application()
	: m_initialized(false)
	, m_running(false)
	, m_window(nullptr)
	, m_glContext(nullptr)
	, m_previousTime(0.0)
{
}

Application::~Application()
{
}

bool Application::init(int width, int height, const char* name)
{
	if (!m_initialized)
	{
		/*if (!glfwInit())
		{
			LOG_ERROR("ERROR: Application::init -> glfw initialization failed.");
			return false;
		}
		glfwSetErrorCallback(glfw_errorCallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		// NOTE: Maybe window should be opened only when start is called
		m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			LOG_ERROR("ERROR: Application::init -> glfw window creation failed.");
			return false;
		}

		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, glfw_keyCallback);
		glfwSetCharCallback(m_window, glfw_charCallback);
		glfwSetMouseButtonCallback(m_window, glfw_mouseButtonCallback);
		glfwSetScrollCallback(m_window, glfw_scrollCallback);

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1); // VSYNC*/

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			LOG_ERROR("Failed to initialize SDL: %s.", SDL_GetError());
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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

	m_clock.start();
	m_previousTime = m_clock.getTime().asSeconds();

	started();

	m_running = true;
	while(m_running)
	{
		// GAME LOOP
		_processEvents();
		_update();
		_render();

		g_resourceManager.flushResources();
	}

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

const Clock& Application::getClock() const
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

void Application::_update()
{
	ImGui_ImplSdlGL3_NewFrame();
	double time = m_previousTime = m_clock.getTime().asSeconds();
	float dt = static_cast<float>(time - m_previousTime);
	m_previousTime = time;
	update(dt);
}

void Application::_render()
{
	render();
	ImGui::Render();
	SDL_GL_SwapWindow(m_window);
}
