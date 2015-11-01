#include "stdafx.h"
#include "BlonkApp.h"
#include "core/File.h"
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

void BlonkApp::started()
{
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
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof (float), points, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glVertexAttribPointer(aPostionLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(aPostionLocation);

	ib = 0;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint16), indices, GL_STATIC_DRAW);
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

	ImGui::SliderFloat("distance", &distance, .6f, 2.f);
	ImGui::DragFloat("angle", &angle, 0.01f);

	glm::mat4 projection = glm::perspective(5.f, windowRatio, 0.001f, 1000.f);
	glm::vec4 camPos = glm::vec4(0.f, 0.f, 0.f, 1.f);
	camPos[2] += distance;
	glm::mat4 view = glm::rotate(glm::mat4(), angle, glm::vec3(0.f, 1.f, 0.f));
	view =  glm::translate(view, glm::vec3(camPos));

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