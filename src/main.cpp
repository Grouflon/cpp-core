#include "stdafx.h"

#include "SandboxApp.h"

int main(int argc, char** argv)
{
	SandboxApp app;
	if (!app.init(800, 600, "playground"))
	{
		std::cerr << "main -> Failed to initialize application." << std::endl;
		return EXIT_FAILURE;
	}

	app.start();
	//app.shutdown();

	return EXIT_SUCCESS;
}