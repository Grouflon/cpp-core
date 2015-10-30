﻿#include "stdafx.h"
#include "core/Application.h"

#include <imgui_impl_glfw_gl3.h>

#include "core/ResourceManager.h"

void glfw_errorCallback(int error, const char* descritpion)
{
	std::cerr << "Error " << error << ": " << descritpion << std::endl;
}

Application::Application()
	: m_initialized(false)
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
			std::cerr << "Application::init -> glfw initialization failed." << std::endl;
			return false;
		}
		glfwSetErrorCallback(glfw_errorCallback);

		m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			std::cerr << "Application::init -> glfw window creation failed." << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1); // VSYNC

		if (gl3wInit() == -1)
		{
			std::cerr << "Application::init -> gl3w initialization failed." << std::endl;
			return false;
		}

		if (!ImGui_ImplGlfwGL3_Init(m_window, true))// pass to false and call callbacks manually when we have custom callbacks
		{
			std::cerr << "Application::init -> ImGui initialization failed." << std::endl;
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
