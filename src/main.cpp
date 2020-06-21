#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "iostream"

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glEnableVertexAttribArray(0);
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3)));
        GLCall(glDisableVertexAttribArray(0));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}