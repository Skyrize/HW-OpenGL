#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "GL/glew.h"
#include <GLM/glm.hpp>			// Add helper maths library
class Shader
{
private:
	std::unordered_map<std::string, GLint> uniformLocationCache;
	std::vector<std::string> filePathes;
	GLuint rendererID = 0;
public:
	Shader();
	~Shader();

	void Generate();
	void Validate() const;
	void Bind() const;
	void Unbind() const;

	// Set Uniforms

	void SetUniform1f(const std::string& name, GLfloat value);
	void SetUniform1i(const std::string& name, GLint value);
	void SetUniform1iv(const std::string& name, GLsizei size, GLint* pointer);
	void SetUniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2);
	void SetUniform3f(const std::string& name, glm::vec3 v);
	void SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniform4f(const std::string& name, glm::vec3 v, GLfloat v3);
	void SetUniform4f(const std::string& name, glm::vec4 v);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4 &mat);
	GLuint CreateShader(std::string filePath, GLenum type);

private:
	GLint GetUniformLocation(const std::string& name);
	GLuint CompileShader(GLenum type, const std::string& source);
	void CheckErrorShader(GLuint shader, std::string filePath);

};

