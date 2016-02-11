#pragma once

#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();

	void setMatrix(const glm::mat4& _value);
	glm::mat4 getMatrix() const;

	static Camera Perspective(float _fov, float _aspect, float _znear = 0.01f, float _zfar = 1000.f);
	static Camera Ortho(float _left, float _right, float _top, float _bottom, float _znear = 0.01f, float _zfar = 1000.f);

private:
	glm::mat4 m_matrix;
};