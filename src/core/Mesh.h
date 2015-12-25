#pragma once

#include <string>

#include "core/Resource.h"

class Mesh : public Resource
{
public:
	Mesh(const char* path);
	virtual ~Mesh();

	virtual void onLoad() override;
	virtual void onRelease() override;

private:
	float*	m_vertices;
	float*	m_uvs;
	float*	m_normals;
	uint32*	m_indices;

	size_t m_vertexCount;
	size_t m_indexCount;

	std::string	m_name;
	std::string m_path;
};