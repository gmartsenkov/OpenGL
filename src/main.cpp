#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


int main() {
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
    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

    static const float g_vertex_buffer_data[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f
    };

    static const unsigned int indices_buffer_data[] = {
            0, 1, 2,
            2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray *va = new VertexArray();
    VertexBuffer *vb = new VertexBuffer(g_vertex_buffer_data, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va->AddBuffer(*vb, layout);

    IndexBuffer *ib = new IndexBuffer(indices_buffer_data, 6);

    Shader *shader = new Shader("../res/shaders/BasicVertex.shader", "../res/shaders/BasicFragment.shader");
    shader->Bind();
    shader->SetUniform4f("u_Color", 1.0f, 0.3f, 0.8f, 1.0f);

    Texture* texture = new Texture("../res/textures/dog.png");
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);

    va->UnBind();
    vb->Unbind();
    ib->Unbind();
    shader->Unbind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        renderer.Clear();

        shader->Bind();
        shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        if (r > 1.0f)
            increment = -0.01f;
        else if (r < 0.0f)
            increment = 0.05;

        r += increment;

        renderer.Draw(*va, *ib, *shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete vb;
    delete ib;
    delete va;
    delete shader;
    delete texture;

    glfwTerminate();
    return 0;
}