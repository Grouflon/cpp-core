#include "stdafx.h"
#include "BlonkApp.h"

#include "core/File.h"
#include "core/BinarySerializer.h"
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
	float cameraVerticalAngle;
	float cameraDistance;
	float fov;
};

static GameData		g_gameData;
static const char*	gameDataPath = "data/game.data";
static Box*			box;

void BlonkApp::started()
{
	if (!_loadGameData())
	{
		g_gameData.cameraVerticalAngle = 45.f;
		g_gameData.cameraDistance = 10.f;
		g_gameData.fov = degToRad(55.f);
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
	ImGui::SliderFloat("distance", &g_gameData.cameraDistance, 0.f, 100.f);
	ImGui::SliderFloat("angle", &g_gameData.cameraVerticalAngle, 0.f, 90.f);
	ImGui::SliderFloat("fov", &g_gameData.fov, 5.f, 180.f);
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
			LOG_ERROR("ERROR: failed to save game data.");
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
	glDisable(GL_CULL_FACE);

	glm::mat4 projection = glm::perspective(degToRad(g_gameData.fov), windowRatio, 0.001f, 1000.f);

	glm::mat4 view = glm::rotate(glm::mat4(), degToRad(45.f), glm::vec3(0.f, 1.f, 0.f));
	view = glm::rotate(view, degToRad(-g_gameData.cameraVerticalAngle), glm::vec3(1.f, 0.f, 0.f));
	view = glm::translate(view, glm::vec3(glm::vec3(0.f, 0.f, g_gameData.cameraDistance)));

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
	BinarySerializer serializer;
	File file(gameDataPath);
	bool result = file.open(File::MODE_WRITE);
	serializer.beginWrite(&file);

	result = result && serializer.serialize("cameraDistance", g_gameData.cameraDistance);
	result = result && serializer.serialize("cameraVerticalAngle", g_gameData.cameraVerticalAngle);
	result = result && serializer.serialize("fov", g_gameData.fov);

	serializer.end();
	file.close();
	return result;
}

bool BlonkApp::_loadGameData()
{
	BinarySerializer serializer;
	File file(gameDataPath);
	bool result = file.open(File::MODE_READ);
	serializer.beginRead(&file);

	result = result && serializer.serialize("cameraDistance", g_gameData.cameraDistance);
	result = result && serializer.serialize("cameraVerticalAngle", g_gameData.cameraVerticalAngle);
	result = result && serializer.serialize("fov", g_gameData.fov);

	serializer.end();
	file.close();
	return result;
}