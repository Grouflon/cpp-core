#include "stdafx.h"

#include "core/Application.h"

int main(int argc, char** argv)
{
	Application app;
	if (!app.init(800, 600, "playground"))
	{
		std::cerr << "main -> Failed to initialize application." << std::endl;
		return EXIT_FAILURE;
	}

	app.start();
	app.shutdown();

	return EXIT_SUCCESS;
}