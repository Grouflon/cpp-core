#include "stdafx.h"
#include "Box.h"

#include "core/ShaderManager.h"

Box::Box(const glm::vec3& position, const glm::vec3& dimensions)
	: m_initialized(false)
	, m_dimensions(dimensions)
	, m_shaderProgram(0)
	, m_aPosition(0)
	, m_aNormal(0)
	, m_uModelLocation(0)
	, m_vao(0)
	, m_indexBuffer(0)
{
	m_transform.setTranslation(position);
}

Box::~Box()
{
}

bool Box::init()
{
	m_shaderProgram = ShaderManager::getShaderProgram("default");
	if (m_shaderProgram == INVALID_SHADER_PROGRAM)
	{
		return false;
	}

	m_aPosition = glGetAttribLocation(m_shaderProgram, "aPosition");
	m_aNormal = glGetAttribLocation(m_shaderProgram, "aNormal");
	m_uModelLocation = glGetUniformLocation(m_shaderProgram, "uModel");

	float normals[] = {
		// FRONT
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		// BACK
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		// TOP
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		// BOTTOM
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		// RIGHT
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		// LEFT
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	uint16 indices[] = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(2, m_vbo);
	_updateVertices();
	glVertexAttribPointer(m_aPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(m_aPosition);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(m_aNormal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(m_aNormal);

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_initialized = true;
	return true;
}

void Box::shutdown()
{
	glDeleteBuffers(2, m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_indexBuffer);
	m_initialized = false;
}

void Box::render()
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vao);
	glUniformMatrix4fv(m_uModelLocation, 1, GL_FALSE, glm::value_ptr(m_transform.getWorldMatrix()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
}

Transform& Box::getTransform()
{
	return m_transform;
}

void Box::_updateVertices()
{
	float w = m_dimensions[0] * 0.5f;
	float h = m_dimensions[1] * 0.5f;
	float d = m_dimensions[2] * 0.5f;
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

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}