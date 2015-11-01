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

static GLuint vao;
static GLuint vbo;

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

	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof (float), points, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint aPostionLocation = glGetAttribLocation(shaderProgram, "aPosition");
	glEnableVertexAttribArray(aPostionLocation);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(aPostionLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void BlonkApp::render()
{
	uint16 indices[] = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
}