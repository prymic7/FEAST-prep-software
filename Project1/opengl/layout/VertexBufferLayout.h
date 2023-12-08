#pragma once
#include "../errorHandlers/ErrorHandler.h"
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

struct VertexBufferElement
{
	GLuint type;
	GLuint count;
	unsigned char normalized;

	static GLuint GetSizeOfType(GLuint type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
		ASSERT(false);
	}
};
class VertexBufferLayout
{

	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;

public:
	VertexBufferLayout() : m_Stride(0) {};

	template<typename T>
	void Push(GLuint count)
	{
		std::runtime_error("kokot");
	}

	template<>
	void Push<float>(GLuint count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<GLuint>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<glm::vec2>(GLuint count)
	{
		m_Elements.push_back({ GL_FLOAT, count*2, GL_FALSE });
		m_Stride += count * sizeof(glm::vec2);
	}

	template<>
	void Push<unsigned char*>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);

	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; } // return const&
	inline GLuint GetStride() const { return m_Stride; };
};

