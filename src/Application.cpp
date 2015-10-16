#include "Application.h"
#include <SFML/OpenGL.hpp>
#include <imgui.h>
#include "imgui_impl_sfml.h"

Application::Application()
	: m_initialized(false)
	, m_running(false)
{
}

Application::~Application()
{
}

void Application::init(int width, int height, const char* name)
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
			// TODO: Error, make function return a bool;
		};

		m_initialized = true;
	}
	else
	{
		// TODO: Assert and shutdown/init again;
	}
}

void Application::shutdown()
{
	if (m_initialized)
	{
		ImGui_ImplSfml_Shutdown();
	}
	else
	{
		// TODO: Assert
	}
}

void Application::start()
{
	// TODO: Assert initialized;

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

			default:
				{

				} break;
			}
		}
		ImGui_ImplSfml_NewFrame(&m_window);

		// CODE HERE
		ImGui::ShowTestWindow();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui::Render();
		m_window.display();
	}
}

void Application::requestStop()
{
	m_running = false;
}