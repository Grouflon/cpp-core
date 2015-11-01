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
	void	_updateVbo();

	bool		m_initialized;

	glm::vec3	m_dimensions;
	Transform	m_transform;

	GLuint		m_shaderProgram;
	GLuint		m_uModelLocation;
	GLuint		m_vbo;
	GLuint		m_vao;
	GLuint		m_indexBuffer;
};
