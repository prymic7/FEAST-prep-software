#pragma once

#include "../errorHandlers/ErrorHandler.h"
#include <glew.h>
class IndexBuffer
{

	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer(unsigned int count, const GLushort* data);
	~IndexBuffer();

	void Init(unsigned int count, const GLushort* data);
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }	
};

