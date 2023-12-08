#pragma once
#include <vector>
#include "../../opengl/errorHandlers/ErrorHandler.h"
#include <glew.h>
#include <stb_image.h>
#include <wx/wx.h>
class STBimage
{

	std::vector<float> vertices;
	int width;
	int height;
	int channels;
	GLuint m_RendererID;
	std::string imagePath;
	unsigned char* imageData;
		

public:
	STBimage(std::string imagePath);
	~STBimage();


	void Bind(GLuint slot = 0) const;
	void Unbind() const;








};

