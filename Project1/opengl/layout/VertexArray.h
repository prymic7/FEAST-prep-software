#pragma once
#include "VertexBufferLayout.h"
#include "../buffers/VertexBuffer.h"
class VertexArray
{
	GLuint m_GeneratedID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);

	void Init();
	void Bind() const;
	void Unbind() const;

};

