#pragma once
#include <unordered_map>
#include "../errorHandlers/ErrorHandler.h"


class ShaderProgram
{
	GLuint m_GeneratedID;
	const std::string& m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	struct ShaderProgramSource
	{
		std::string VertexShader;
		std::string FragmentShader;
	};

	ShaderProgramSource ParseShader(const std::string& filePath);
	GLuint CreateShader(unsigned int type, const std::string& source);
	GLuint CreateProgram(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
public:
	ShaderProgram(const std::string& filePath);
	~ShaderProgram();

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float n0, float n1, float n2, float n3);
	void SetUniformMatrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value); //GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
	void SetUniform2f(const std::string& name, float n0, float n1);
	void SetUniform1f(const std::string& name, float n0);
	void SetUniform3f(const std::string& name, float n0, float n1, float n2);

	bool FileExists(const std::string& filePath);
	void Bind() const;
	void Unbind() const;
	GLint GetID() const;

};



