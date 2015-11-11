#include "stdafx.h"
#include "core/Application.h"

#include <imgui_impl_glfw_gl3.h>

#include "core/ResourceManager.h"

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
}


Application::Application()
	: m_initialized(false)
	, m_window(nullptr)
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
		if (!glfwInit())
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
		glfwSwapInterval(1); // VSYNC

		if (gl3wInit() == -1)
		{
			LOG_ERROR("ERROR: Application::init -> gl3w initialization failed.");
			return false;
		}

		if (!ImGui_ImplGlfwGL3_Init(m_window, false)) // pass to false and call callbacks manually when we have custom callbacks
		{
			LOG_ERROR("ERROR: Application::init -> ImGui initialization failed.");
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
		ImGui_ImplGlfwGL3_Shutdown();
		glfwDestroyWindow(m_window);
		glfwTerminate();

		m_window = nullptr;
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

	started();

	m_previousTime = glfwGetTime();

	while(!glfwWindowShouldClose(m_window))
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
	glfwSetWindowShouldClose(m_window, GL_TRUE);
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

void Application::onKeyEvent(int key, int scancode, int action, int mods)
{
}

void Application::onCharEvent(char c)
{
}

glm::ivec2 Application::getWindowSize() const
{
	glm::ivec2 size;
	glfwGetWindowSize(m_window, &size[0], &size[1]);
	return size;
}

float Application::getWindowRatio() const
{
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	return static_cast<float>(w) / static_cast<float>(h);
}

const Clock& Application::getClock() const
{
	return m_clock;
}

void Application::_processEvents()
{
	glfwPollEvents();
}

void Application::_update()
{
	ImGui_ImplGlfwGL3_NewFrame();
	double time = glfwGetTime();
	float dt = static_cast<float>(time - m_previousTime);
	m_previousTime = time;
	update(dt);
}

void Application::_render()
{
	render();
	ImGui::Render();
	glfwSwapBuffers(m_window);
}
