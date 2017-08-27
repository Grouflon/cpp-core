#pragma once

#include <GL/gl3w.h>
#include <unordered_map>

#include "core/StringHash.h"

#define INVALID_SHADER_PROGRAM	0

class ShaderManager
{
public:
	static GLuint	loadShaderProgram(const char* name, const char* vertexShaderpath, const char* fragmentShaderPath);
	static GLuint	getShaderProgram(const char* name);

	// TODO: destroy shaders ? is that useful ?

private:
	static std::unordered_map<StringHash, GLuint>	s_shaderPrograms;
};
