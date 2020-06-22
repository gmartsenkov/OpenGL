#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

static std::string GetShader(const std::string& file)
{
    std::ifstream stream(file);
    std::string line;
    std::stringstream fileContent;

    while (getline(stream, line))
        fileContent << line + "\n";

    return fileContent.str();
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
   unsigned int id = glCreateShader(type);
   const char* src = source.c_str();
   glShaderSource(id, 1, &src, nullptr);
   glCompileShader(id);

   int result;
   glGetShaderiv(id, GL_COMPILE_STATUS, &result);

   if (result == GL_FALSE)
   {
       int length;
       glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
       char* message = (char*)_malloca(length * sizeof(char ));
       glGetShaderInfoLog(id, length, &length, message);

       std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl;
       std::cout << message << std::endl;
       glDeleteShader(id);
   }

   return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
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

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

    unsigned int VertexArrayID;
    GLCall(glGenVertexArrays(1, &VertexArrayID));
    GLCall(glBindVertexArray(VertexArrayID));

    static const float g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
    };

    unsigned int vertexBuffer;
    GLCall(glGenBuffers(1, &vertexBuffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));

    std::string VertexShader = GetShader("../res/shaders/BasicVertex.shader");
    std::string FragmentShader = GetShader("../res/shaders/BasicFragment.shader");

    unsigned int shader = CreateShader(VertexShader, FragmentShader);
    GLCall(glUseProgram(shader));
    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));
        GLCall(glBindVertexArray(VertexArrayID));

        GLCall(glEnableVertexAttribArray(0);
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3)));
        GLCall(glDisableVertexAttribArray(0));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        glDeleteProgram(shader);
    }

    glfwTerminate();
    return 0;
}