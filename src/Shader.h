#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader {
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string &vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
    std::string GetShader(const std::string& filepath);
    int GetUniformLocation(const std::string& name);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    bool CompileShader();
};
