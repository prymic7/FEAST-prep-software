#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int size, const void* data, const std::string type)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    if (type == "static")
    {
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); 
    }
    else if (type == "dynamic")
    {
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }
    else
    {
        
        wxMessageBox(type.c_str(), " <-- wrong type of buffer(only static or draw needed)", wxICON_ERROR | wxOK);
    }
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}


void VertexBuffer::SubData(unsigned int size, const void* data)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    wxString str = wxString::Format("%d", size);
    //wxLogStatus(str);
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
