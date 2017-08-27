#include "core/Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
	: m_scale(glm::vec3(1.f))
	, m_parent(nullptr)
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	, m_dirty(true)
#endif
{
}

Transform::~Transform()
{
}

void Transform::setTranslation(float x, float y, float z)
{
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	if (x != m_translation[0] || y != m_translation[1] || z != m_translation[2])
		m_dirty = true;
#endif

	m_translation[0] = x;
	m_translation[1] = y;
	m_translation[2] = z;
}

void Transform::setTranslation(const glm::vec3& v)
{
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	if (v != m_translation)
		m_dirty = true;
#endif

	m_translation = v;
}

glm::vec3 Transform::getTranslation() const
{
	return m_translation;
}

void Transform::setRotation(float i, float j, float k, float w)
{
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	if (i != m_rotation[0] || j != m_rotation[1] || k != m_rotation[2] || w != m_rotation[3])
		m_dirty = true;
#endif

	m_rotation[0] = i;
	m_rotation[1] = j;
	m_rotation[2] = k;
	m_rotation[3] = w;
}

void Transform::setRotation(glm::quat& q)
{
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	if (q != m_rotation)
		m_dirty = true;
#endif

	m_rotation = q;
}

glm::quat Transform::getRotation() const
{
	return m_rotation;
}

void Transform::setScale(float x, float y, float z)
{
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	if (x != m_scale[0] || y != m_scale[1] || z != m_scale[2])
		m_dirty = true;
#endif

	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

void Transform::setScale(const glm::vec3& v)
{
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	if (v != m_scale)
		m_dirty = true;
#endif

	m_scale = v;
}

glm::vec3 Transform::getScale() const
{
	return m_scale;
}

void Transform::setParent(Transform* parent)
{
	m_parent = parent;
}

Transform* Transform::getParent() const
{
	return m_parent;
}

glm::mat4 Transform::getLocalMatrix() const
{
#ifdef TRANSFORM_LOCALMATRIX_CACHE
	if (!m_dirty)
		return m_localMatrix;
#endif

	glm::mat4 localMatrix = glm::scale(glm::mat4(), m_scale) * glm::mat4_cast(m_rotation) * glm::translate(glm::mat4(), m_translation);

#ifdef TRANSFORM_LOCALMATRIX_CACHE
	m_dirty = false;
	m_localMatrix = localMatrix;
#endif

	return localMatrix;
}

glm::mat4 Transform::getWorldMatrix() const
{
	if (m_parent)
	{
		return m_parent->getWorldMatrix() * getLocalMatrix();
	}
	else
	{
		return getLocalMatrix();
	}
}