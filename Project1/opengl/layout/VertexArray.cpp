#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glCreateVertexArrays(1, &m_GeneratedID));
	GLCall(glBindVertexArray(m_GeneratedID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_GeneratedID));
}


void VertexArray::Init()
{
	
}

void VertexArray::AddBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout)
{
	Bind();
	vb->Bind();
	const auto& elements = layout->GetElements();
	GLuint offset = 0;
	for (GLuint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_GeneratedID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
