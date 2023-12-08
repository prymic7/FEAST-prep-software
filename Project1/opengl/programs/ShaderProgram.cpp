#include "ShaderProgram.h"
#include <fstream>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

ShaderProgram::ShaderProgram(const std::string& filePath) : m_GeneratedID(0), m_FilePath(filePath)
{

    ShaderProgramSource source = ParseShader(filePath);
    m_GeneratedID = CreateProgram(source.VertexShader, source.FragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    GLCall(glDeleteProgram(m_GeneratedID));
}

bool ShaderProgram::FileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

ShaderProgram::ShaderProgramSource ShaderProgram::ParseShader(const std::string& filePath)
{
    if (!FileExists(filePath)) {
        wxLogStatus("Shader file not found!");
    }

    std::ifstream stream(filePath);
    std::string line;
    std::stringstream ss[2];
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;

            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

GLuint ShaderProgram::CreateShader(GLuint type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        char* message = new char[logLength];
        glGetShaderInfoLog(id, logLength, &logLength, message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

GLuint ShaderProgram::CreateProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint program = glCreateProgram();
    unsigned int vs = CreateShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void ShaderProgram::Bind() const
{
    GLCall(glUseProgram(m_GeneratedID));
}

void ShaderProgram::Unbind() const
{
    GLCall(glUseProgram(0));
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return  m_UniformLocationCache[name];
    }
    GLCall(int location = glGetUniformLocation(m_GeneratedID, name.c_str()));
    if (location == -1)
    {
        wxString errorMessage = "Error! Uniform with name " + wxString(name) + " doesn't exist";
        wxLogStatus(errorMessage);
    }

    m_UniformLocationCache[name] = location;

    return location;
}

void ShaderProgram::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value))
}

void ShaderProgram::SetUniform4f(const std::string& name, float n0, float n1, float n2, float n3)
{
    GLCall(glUniform4f(GetUniformLocation(name), n0, n1, n2, n3));

}

void ShaderProgram::SetUniformMatrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), count, transpose, value));
}

void ShaderProgram::SetUniform3f(const std::string& name, float n0, float n1, float n2)
{
    GLCall(glUniform3f(GetUniformLocation(name), n0, n1, n2));
}

void ShaderProgram::SetUniform2f(const std::string& name, float n0, float n1)
{
    GLCall(glUniform2f(GetUniformLocation(name), n0, n1));
}

void ShaderProgram::SetUniform1f(const std::string& name, float n0)
{
    GLCall(glUniform1f(GetUniformLocation(name), n0));
}


GLint ShaderProgram::GetID() const { return m_GeneratedID; }

