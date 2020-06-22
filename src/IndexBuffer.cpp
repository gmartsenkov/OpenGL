#include "Renderer.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RenderId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RenderId));
}

void IndexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId));
}

void IndexBuffer::Unbind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
