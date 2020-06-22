#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string &vertexPath, const std::string& fragmentPath)
    : m_RendererID(0) {
    std::string VertexShader = GetShader(vertexPath);
    std::string FragmentShader = GetShader(fragmentPath);

    m_RendererID = CreateShader(VertexShader, FragmentShader);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string &name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3))
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}

bool Shader::CompileShader() {
    return false;
}

std::string Shader::GetShader(const std::string &file) {
    std::ifstream stream(file);
    std::string line;
    std::stringstream fileContent;

    while (getline(stream, line))
        fileContent << line + "\n";

    return fileContent.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) _malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}
