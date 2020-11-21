#include "Shader.h"
#include "Asset.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

Shader::Shader()
{
}

void Shader::Generate()
{
	rendererID = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(rendererID);
}

void Shader::Validate() const
{
	glLinkProgram(rendererID);
	glValidateProgram(rendererID);
}

void Shader::Bind() const
{
	glUseProgram(rendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1f(const std::string& name, GLfloat value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, GLint value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1iv(const std::string& name, GLsizei size, GLint* pointer)
{
	glUniform1iv(GetUniformLocation(name), size, pointer);
}

void Shader::SetUniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 v)
{
	glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
}

void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4f(const std::string& name, glm::vec3 v, GLfloat v3)
{
	glUniform4f(GetUniformLocation(name), v.x, v.y , v.z, v3);
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 v)
{
	glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4 &mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]); //might cause problems with ref
}

GLint Shader::GetUniformLocation(const std::string& name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
		return uniformLocationCache[name];
	}
	auto location = glGetUniformLocation(rendererID, name.c_str());

	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' doesn't exist." << std::endl;
	}
	uniformLocationCache[name] = location;
	return location;
}

GLuint Shader::CompileShader(GLenum type, const std::string& source)
{
	auto id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

GLuint Shader::CreateShader(std::string filePath, GLenum type)
{
	std::string sourceString = Asset::ReadFile(filePath);
	const char* source = sourceString.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	CheckErrorShader(shader, filePath);
	glAttachShader(rendererID, shader);
	filePathes.push_back(filePath);
	return shader;
}

void Shader::CheckErrorShader(GLuint shader, std::string filePath) {
	GLint result;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_TRUE)
		return;

	// Get log lenght
	GLint maxLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

	// Init a string for it
	std::vector<GLchar> errorLog(maxLength);

	if (maxLength > 1) {
		// Get the log file
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		std::cout << "--------------Shader '" << filePath << "' compilation error-------------\n";
		std::cout << errorLog.data();
	}
}
