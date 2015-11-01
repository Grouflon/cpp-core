#pragma once

#include "core/Transform.h"

class Box
{
public:
	Box(const glm::vec3& position, const glm::vec3& dimensions);
	~Box();

	bool init();
	void shutdown();
	void render();

	Transform& getTransform();

private:
	void	_updateVertices();

	bool		m_initialized;

	glm::vec3	m_dimensions;
	Transform	m_transform;

	GLuint		m_shaderProgram;
	GLuint		m_aPosition;
	GLuint		m_aNormal;
	GLuint		m_uModelLocation;
	GLuint		m_vbo[2];
	GLuint		m_vao;
	GLuint		m_indexBuffer;
};
