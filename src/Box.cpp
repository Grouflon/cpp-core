#include "stdafx.h"
#include "Box.h"

#include "core/ShaderManager.h"

Box::Box(const glm::vec3& position, const glm::vec3& dimensions)
	: m_initialized(false)
	, m_dimensions(dimensions)
	, m_shaderProgram(0)
	, m_uModelLocation(0)
	, m_vbo(0)
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

	GLuint aPositionLocation = glGetAttribLocation(m_shaderProgram, "aPosition");
	m_uModelLocation = glGetUniformLocation(m_shaderProgram, "uModel");

	uint16 indices[] = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(aPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(aPositionLocation);

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_initialized = true;

	_updateVbo();
	return true;
}

void Box::shutdown()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_indexBuffer);
	m_initialized = false;
}

void Box::render()
{
	glUseProgram(m_shaderProgram);
	glUniformMatrix4fv(m_uModelLocation, 1, GL_FALSE, glm::value_ptr(m_transform.getWorldMatrix()));
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
}

Transform& Box::getTransform()
{
	return m_transform;
}

void Box::_updateVbo()
{
	ASSERT(m_initialized);

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

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}