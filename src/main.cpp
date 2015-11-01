#include "stdafx.h"

#include "BlonkApp.h"

int main(int argc, char** argv)
{
	BlonkApp app;
	if (!app.init(800, 600, "playground"))
	{
		LOG_ERROR("ERROR: main -> Failed to initialize application.");
		return EXIT_FAILURE;
	}

	app.start();
	//app.shutdown();

	return EXIT_SUCCESS;
}