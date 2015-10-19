#include "stdafx.h"
#include "core/Application.h"

#include <imgui_impl_sfml.h>

#include "core/ResourceManager.h"
#include "core/RenderContext.h"

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

	onStart();

	m_clock.restart();

	m_running = true;
	while(m_running)
	{
		// GAME LOOP
		_processEvents();
		_update();
		_render();

		g_resourceManager.flushResources();
	}

	onStop();
}

void Application::requestStop()
{
	m_running = false;
}

void Application::onStart()
{
}

void Application::onRender(RenderContext*)
{
}

void Application::onUpdate(float)
{
}

void Application::onStop()
{
}

void Application::_processEvents()
{
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
			break;
		}
	}
}

void Application::_update()
{
	ImGui_ImplSfml_NewFrame(&m_window);
	float dt = m_clock.restart().asSeconds();
	onUpdate(dt);
}

void Application::_render()
{
	RenderContext ctx;
	ctx.clear();
	onRender(&ctx);
	ImGui::Render();
	m_window.display();
}
