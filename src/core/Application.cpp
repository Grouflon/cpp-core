#include "stdafx.h"
#include "core/Application.h"

#include <imgui_impl_glfw_gl3.h>

#include "core/ResourceManager.h"

void glfw_errorCallback(int error, const char* description)
{
	LOG_ERROR("ERROR: GLFW ERROR: code %d msg: %s", error, description);
	ASSERT(false);
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

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1); // VSYNC

		if (gl3wInit() == -1)
		{
			LOG_ERROR("ERROR: Application::init -> gl3w initialization failed.");
			return false;
		}

		if (!ImGui_ImplGlfwGL3_Init(m_window, true)) // pass to false and call callbacks manually when we have custom callbacks
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
	ASSERT(m_initialized) // Should not call start before init

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
	glfwSwapBuffers(m_window);
	ImGui::Render();
}
