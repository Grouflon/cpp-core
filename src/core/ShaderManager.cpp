#include "stdafx.h"
#include "core/ShaderManager.h"

#include "core/File.h"

std::unordered_map<StringHash, GLuint> ShaderManager::s_shaderPrograms;

GLuint ShaderManager::loadShaderProgram(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath)
{
	// RETURN AN ERROR IF NAME IS ALREADY REGISTERED
	auto it = s_shaderPrograms.find(name);
	if (it != s_shaderPrograms.end())
	{
		LOG_ERROR("ERROR: ShaderManager::loadShaderProgram -> Shader \"%s\" is already loaded.", name);
	}

	// VERTEX SHADER
	GLuint vs = 0;
	{
		char* shaderSource;
		File file(vertexShaderPath);
		if (file.open(File::MODE_READ))
		{
			size_t size = file.getSize();
			shaderSource = new char[size + 1];
			file.read(shaderSource, size);
			shaderSource[size] = 0;
			file.close();
		}
		else
		{
			LOG_ERROR("ERROR: ShaderManager::loadShaderProgram -> Failed to open file \"%s\".", vertexShaderPath);
			return INVALID_SHADER_PROGRAM;
		}

		vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &shaderSource, nullptr);
		glCompileShader(vs);
		delete[] shaderSource;

		int params = -1;
		glGetShaderiv (vs, GL_COMPILE_STATUS, &params);
		if (GL_TRUE != params) {
			int max_length = 2048;
			int actual_length = 0;
			char log[2048];
			glGetShaderInfoLog (vs, max_length, &actual_length, log);
			LOG_ERROR("ERROR: ShaderManager::loadShaderProgram -> Shader \"%s\" failed to compile:\n%s", vertexShaderPath, log);

			return INVALID_SHADER_PROGRAM;
		}
	}

	// FRAGMENT SHADER
	GLuint fs = 0;
	{
		char* shaderSource;
		File file(fragmentShaderPath);
		if (file.open(File::MODE_READ))
		{
			size_t size = file.getSize();
			shaderSource = new char[size + 1];
			file.read(shaderSource, size);
			shaderSource[size] = 0;
			file.close();
		}
		else
		{
			LOG_ERROR("ERROR: ShaderManager::loadShaderProgram -> Failed to open file \"%s\".", fragmentShaderPath);
			return INVALID_SHADER_PROGRAM;
		}

		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &shaderSource, nullptr);
		glCompileShader(fs);
		delete[] shaderSource;

		int params = -1;
		glGetShaderiv (fs, GL_COMPILE_STATUS, &params);
		if (GL_TRUE != params) {
			int max_length = 2048;
			int actual_length = 0;
			char log[2048];
			glGetShaderInfoLog (vs, max_length, &actual_length, log);
			LOG_ERROR("ERROR: ShaderManager::loadShaderProgram -> Shader \"%s\" failed to compile:\n%s", fragmentShaderPath, log);

			glDeleteShader(vs);
			return INVALID_SHADER_PROGRAM;
		}
	}

	// PROGRAM
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int params = -1;
	glGetProgramiv (program, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		int max_length = 2048;
		int actual_length = 0;
		char log[2048];
		glGetProgramInfoLog (program, max_length, &actual_length, log);
		LOG_ERROR("ERROR: ShaderManager::loadShaderProgram -> Shader Program \"%s\" failed to link:\n%s", name, log);

		glDeleteShader(vs);
		glDeleteShader(fs);
		glDeleteProgram(program);
		return INVALID_SHADER_PROGRAM;
	}

	s_shaderPrograms.insert(std::pair<StringHash, GLuint>(StringHash(name), program));

	return program;
}

GLuint ShaderManager::getShaderProgram(const char* name)
{
	auto it = s_shaderPrograms.find(name);
	if (it != s_shaderPrograms.end())
	{
		return it->second;
	}
	else
	{
		return INVALID_SHADER_PROGRAM;
	}
}
