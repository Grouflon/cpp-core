#include "stdafx.h"
#include "BlonkApp.h"
#include "core/File.h"
#include "core/BinarySerializer.h"
#include "core/ShaderManager.h"

BlonkApp::BlonkApp()
{
}

BlonkApp::~BlonkApp()
{
}

static GLuint aPostionLocation;
static GLuint uMVPLocation;
static GLuint vbo;
static GLuint vao;
static GLuint ib;

static float angle;
static float distance;

struct GameData
{
	float cameraVerticalAngle;
	float cameraDistance;
	float fov;
};

static GameData		g_gameData;
static const char*	gameDataPath = "data/game.data";

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

	glUseProgram(ShaderManager::getShaderProgram("default"));
	aPostionLocation = glGetAttribLocation(shaderProgram, "aPosition");
	uMVPLocation = glGetUniformLocation(shaderProgram, "uMVP");

	float w = 0.5f;
	float h = 0.5f;
	float d = 0.5f;
	float points[] = {
		// FRONT
		-w, -h,  d,
		w, -h,  d,
		w,  h,  d,
		-w,  h,  d,

		// BACK
		w, -h, -d,
		-w, -h, -d,
		-w,  h, -d,
		w,  h, -d,

		// TOP
		w, h, -d,
		-w, h, -d,
		-w, h,  d,
		w, h,  d,

		// BOTTOM
		-w, -h, -d,
		w, -h, -d,
		w, -h,  d,
		-w, -h,  d,

		// RIGHT
		w, -h, -d,
		w,  h, -d,
		w,  h,  d,
		w, -h,  d,

		// LEFT
		-w,  h, -d,
		-w, -h, -d,
		-w, -h,  d,
		-w,  h,  d
	};

	uint16 indices[] = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glVertexAttribPointer(aPostionLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(aPostionLocation);

	ib = 0;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

	glm::mat4 mvp = projection * glm::inverse(view);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBindVertexArray(vao);
	glUniformMatrix4fv(uMVPLocation, 1, GL_FALSE, glm::value_ptr(mvp));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
}

void BlonkApp::onKeyEvent(int key, int scancode, int action, int mods)
{
	LOG("%d %d", key, scancode);
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