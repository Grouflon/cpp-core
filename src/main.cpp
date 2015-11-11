#include "stdafx.h"

#include "BlonkApp.h"
#include "ZonkApp.h"
#include <vld.h>

int main(int argc, char** argv)
{
	ZonkApp app;
	if (!app.init(800, 600, "playground"))
	{
		LOG_ERROR("ERROR: main -> Failed to initialize application.");
		return EXIT_FAILURE;
	}

	app.start();
	app.shutdown();

	for (auto pair : g_stringHashes)
	{
		delete pair.second;
	}
	g_stringHashes.clear();

	return EXIT_SUCCESS;
}