#include "stdafx.h"
#include "ZonkApp.h"

#include "core/StringTools.h"

ZonkApp::ZonkApp()
{
}

ZonkApp::~ZonkApp()
{
}

void ZonkApp::started()
{
}

static char g_query[256];
static int	g_querySize;
static std::string g_log;
static const Clock* g_clock;

static char* g_verbs[] = {
	"look",
	"eat",
	"go"
};

static char* g_nouns[] = {
	"apple",
	"door",
	"dragon"
};

static void log(const char* str)
{
	g_log += "[" + g_clock->getTime().asString() + "] " + str + '\n';
}

static void parseQuery(const char* query, const char** verbs, unsigned int verbCount, const char** nouns, unsigned int nounCount)
{
	std::string q = query;
	lowerCase(q);

	int earliestMatchPos = std::string::npos;
	int match = -1;
	for (auto i = 0u; i < verbCount; ++i)
	{
		int	matchPos = q.find(verbs[i]);
		if (matchPos != std::string::npos)
		{
			if (earliestMatchPos == std::string::npos || matchPos < earliestMatchPos)
			{
				earliestMatchPos = matchPos;
				match = i;
			}
		}
	}

	if (match < 0)
	{
		log("unknown verb");
		return;
	}
	const char* verb = verbs[match];

	earliestMatchPos = std::string::npos;
	match = -1;
	for (auto i = 0u; i < nounCount; ++i)
	{
		int	matchPos = q.find(nouns[i]);
		if (matchPos != std::string::npos)
		{
			if (earliestMatchPos == std::string::npos || matchPos < earliestMatchPos)
			{
				earliestMatchPos = matchPos;
				match = i;
			}
		}
	}

	if (match < 0)
	{
		log("unknown noun");
		return;
	}

	const char* noun = nouns[match];

	std::string action = verb;
	action += " ";
	action += noun;
	log(action.c_str());
}

static void sendQuery()
{
	if (g_querySize > 0)
	{
		log(g_query);
		parseQuery(g_query, (const char**)g_verbs, 3, (const char**)g_nouns, 3);
		g_query[0] = '\0';
		g_querySize = 0;
	}
}



void ZonkApp::update(float dt)
{
	g_clock = &getClock();

	auto size = getWindowSize();

	ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove );
	ImGui::SetWindowPos(ImVec2(0.f, 0.f));
	ImGui::SetWindowSize(ImVec2(size[0], size[1]));

	if (ImGui::Button("Enter"))
	{
		sendQuery();
	}
	ImGui::SameLine();
	ImGui::Text(g_query);

	ImGui::Separator();
	ImGui::Text(g_log.c_str());
	ImGui::End();
}

void ZonkApp::render()
{
	glm::ivec2 windowSize = getWindowSize();
	float windowRatio = getWindowRatio();
	glViewport(0, 0, windowSize[0], windowSize[1]);
	glScissor(0, 0, windowSize[0], windowSize[1]);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void ZonkApp::onKeyEvent(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ENTER || key == GLFW_KEY_KP_ENTER)
		sendQuery();

	if (key == GLFW_KEY_BACKSPACE && g_querySize > 0)
	{
		g_query[--g_querySize] = '\0';
	}
}

void ZonkApp::onCharEvent(char c)
{
	if (g_querySize < 256)
	{
		g_query[g_querySize++] = c;
		g_query[g_querySize] = '\0';
	}
}