#include "stdafx.h"
#include "core/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	m_matrix = glm::mat4(1.f);
}

void Camera::setMatrix(const glm::mat4& _value)
{
	m_matrix = _value;
}

glm::mat4 Camera::getMatrix() const
{
	return m_matrix;
}

Camera Camera::Perspective(float _fov, float _aspect, float _znear /*= 0.01f*/, float _zfar /*= 1000.f*/)
{
	Camera camera;
	camera.setMatrix(glm::perspective(_fov, _aspect, _znear, _zfar));
	return camera;
}

Camera Camera::Ortho(float _left, float _right, float _top, float _bottom, float _znear /*= 0.01f*/, float _zfar /*= 1000.f*/)
{
	Camera camera;
	camera.setMatrix(glm::ortho(_left, _right, _bottom, _top, _znear, _zfar));
	return camera;
}