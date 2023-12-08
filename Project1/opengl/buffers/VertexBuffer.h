#pragma once
#include "../errorHandlers/ErrorHandler.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;


public:
	VertexBuffer(unsigned int size, const void* data, const std::string type);
	~VertexBuffer();

	void SubData(unsigned int size, const void* data);
	void Bind() const;
	void Unbind() const;


};

