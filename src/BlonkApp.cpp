#include "stdafx.h"
#include "BlonkApp.h"

#include "core/File.h"
#include "core/BinarySerializer.h"
#include "core/JsonSerializer.h"
#include "core/Reflection.h"
#include "core/ShaderManager.h"
#include "Box.h"

BlonkApp::BlonkApp()
{
}

BlonkApp::~BlonkApp()
{
}

static GLuint uViewProjection;

struct GameData
{
	REFLECT_BEGIN(GameData)
	REFLECT_AUTO(cameraVerticalAngle)
	REFLECT_AUTO(cameraDistance)
	REFLECT_AUTO(fov)
	REFLECT_ARRAY_AUTO(text, 5);
	REFLECT_END()

	float cameraVerticalAngle;
	float cameraDistance;
	float fov;

	char text[5];
};

static GameData*	g_gameData;
static const char*	jsonGameDataPath = "data/game.json";
static const char*	binGameDataPath = "data/game.data";
static Box*			box;
static bool			g_binary;

void BlonkApp::started()
{
	if (!_loadGameData())
	{
		g_gameData = new GameData;
		g_gameData->cameraVerticalAngle = 45.f;
		g_gameData->cameraDistance = 10.f;
		g_gameData->fov = degToRad(55.f);
	}

	GLuint shaderProgram = ShaderManager::loadShaderProgram("default", "data/shaders/basic_vs.glsl", "data/shaders/basic_fs.glsl");
	if (shaderProgram == INVALID_SHADER_PROGRAM)
	{
		ASSERT(false);
		requestStop();
		return;
	}

	uViewProjection = glGetUniformLocation(shaderProgram, "uViewProjection");


	box = new Box(glm::vec3(0.f, 0.f, 0.f), glm::vec3(2.f, 1.f, 1.f));
	ASSERT(box->init());
}

void BlonkApp::update(float dt)
{
	ImGui::Begin("GameData");

	if (g_gameData)
	{
		ImGui::SliderFloat("distance", &g_gameData->cameraDistance, 0.f, 100.f);
		ImGui::SliderFloat("angle", &g_gameData->cameraVerticalAngle, 0.f, 90.f);
		ImGui::SliderFloat("fov", &g_gameData->fov, 5.f, 180.f);

		ImGui::InputText("text", g_gameData->text, 5);
	}
	
	ImGui::Checkbox("Save as binary", &g_binary);
	if (ImGui::Button("save"))
	{
		if (!_saveGameData())
		{
			LOG_ERROR("ERROR: failed to save game data.");
		}
	}
	if (ImGui::Button("load"))
	{
		if (!_loadGameData())
		{
			LOG_ERROR("ERROR: failed to load game data.");
		}
	}
	ImGui::End();
}

void BlonkApp::render()
{
	glm::ivec2 windowSize = getWindowSize();
	float windowRatio = getWindowRatio();
	glViewport(0, 0, windowSize[0], windowSize[1]);
	glScissor(0, 0, windowSize[0], windowSize[1]);
	glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 projection = glm::perspective(degToRad(g_gameData->fov), windowRatio, 0.001f, 1000.f);

	glm::mat4 view = glm::rotate(glm::mat4(), degToRad(45.f), glm::vec3(0.f, 1.f, 0.f));
	view = glm::rotate(view, degToRad(-g_gameData->cameraVerticalAngle), glm::vec3(1.f, 0.f, 0.f));
	view = glm::translate(view, glm::vec3(glm::vec3(0.f, 0.f, g_gameData->cameraDistance)));

	glm::mat4 vp = projection * glm::inverse(view);

	glUseProgram(ShaderManager::getShaderProgram("default"));
	glUniformMatrix4fv(uViewProjection, 1, GL_FALSE, glm::value_ptr(vp));
	box->render();
}

void BlonkApp::onKeyEvent(int key, int scancode, int action, int mods)
{
}

bool BlonkApp::_saveGameData() const
{
	Serializer* serializer;
	JsonSerializer jsonSerializer;
	BinarySerializer binSerializer;

	const char* dataPath;

	if (g_binary)
	{
		serializer = &binSerializer;
		dataPath = binGameDataPath;
	}
	else
	{
		serializer = &jsonSerializer;
		dataPath = jsonGameDataPath;
	}

	File file(dataPath);
	bool result = file.open(File::MODE_WRITE);
	result = result && serializer->beginWrite(&file);

	result = result && serializer->serialize("gameData", &g_gameData);

	result = result && serializer->end();
	file.close();
	return result;
}

bool BlonkApp::_loadGameData()
{
	Serializer* serializer;
	JsonSerializer jsonSerializer;
	BinarySerializer binSerializer;

	const char* dataPath;

	if (g_binary)
	{
		serializer = &binSerializer;
		dataPath = binGameDataPath;
	}
	else
	{
		serializer = &jsonSerializer;
		dataPath = jsonGameDataPath;
	}

	File file(dataPath);
	bool result = file.open(File::MODE_READ);
	result = result && serializer->beginRead(&file);

	result = result && serializer->serialize("gameData", &g_gameData);

	result = result && serializer->end();
	file.close();
	return result;
}