#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define TRANSFORM_LOCALMATRIX_CACHE

class Transform
{
public:
	Transform();
	~Transform();

	void		setTranslation(float x, float y, float z);
	void		setTranslation(const glm::vec3& v);
	glm::vec3	getTranslation() const;

	void		setRotation(float i, float j, float k, float w);
	void		setRotation(glm::quat& q);
	glm::quat	getRotation() const;

	void		setScale(float x, float y, float z);
	void		setScale(const glm::vec3& v);
	glm::vec3	getScale() const;

	void		setParent(Transform* parent);
	Transform*	getParent() const;

	glm::mat4	getLocalMatrix() const;
	glm::mat4	getWorldMatrix() const;

private:
	// TODO-THINK: Should translate & scale be vec4 ?
	glm::vec3	m_translation;
	glm::quat	m_rotation;
	glm::vec3	m_scale;

	Transform*	m_parent;

#ifdef TRANSFORM_LOCALMATRIX_CACHE
	mutable glm::mat4	m_localMatrix;
	mutable bool		m_dirty;
#endif
};
