﻿#include "stdafx.h"

#include <imgui_impl_sfml.h>

#include "core/Application.h"

Application::Application()
	: m_initialized(false)
	, m_running(false)
{
}

Application::~Application()
{
}

bool Application::init(int width, int height, const char* name)
{
	if (!m_initialized)
	{
		m_window.create(
			sf::VideoMode(width, height),
			name,
			sf::Style::Default,
			sf::ContextSettings(24, 8, 4, 4, 0)
		);

		if (!ImGui_ImplSfml_Init(&m_window))
		{
			std::cerr << "Application::init -> ImGui initialization failed" << std::endl;
			return false;
		};

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
		ImGui_ImplSfml_Shutdown();
	}
	else
	{
		ASSERT(false) // Should not call shutdown two times in a row
	}
}

void Application::start()
{
	ASSERT(m_initialized) // Should not call start before init

	m_running = true;
	while(m_running)
	{
		// GAME LOOP

		sf::Event event;
		while(m_window.pollEvent(event))
		{
			ImGui_ImplSfml_ProcessEvent(&event);

			switch(event.type)
			{
			case sf::Event::Closed:
				{
					requestStop();
				} break;

			case sf::Event::Resized:
				{
					glViewport(0, 0, event.size.width, event.size.height);
				} break;

			default:
				{

				} break;
			}
		}
		ImGui_ImplSfml_NewFrame(&m_window);

		// CODE HERE


		// RENDER
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui::Render();
		m_window.display();
	}
}

void Application::requestStop()
{
	m_running = false;
}