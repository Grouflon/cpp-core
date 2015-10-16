#include <iostream>
#include "Application.h"

int main(int argc, char** argv)
{
	Application app;
	app.init(800, 600, "playground");
	app.start();
	app.shutdown();
	return EXIT_SUCCESS;
}