#pragma once

class VertexBuffer {
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* buffer, unsigned size);
    ~VertexBuffer();
    void Bind();
    void Unbind();
};

