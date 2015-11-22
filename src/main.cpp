#include "stdafx.h"

#include "BlonkApp.h"
#include "ZonkApp.h"

#include "core/Reflection.h"

class Foo
{
	REFLECT_BEGIN(Foo)
	REFLECT_AUTO(m_1)
	REFLECT_AUTO(m_3)
	REFLECT_END()

private:
	int m_1;
	int m_2;
	int m_3;
};


int main(int argc, char** argv)
{
	BlonkApp app;
	if (!app.init(800, 600, "playground"))
	{
		LOG_ERROR("main -> Failed to initialize application.");
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