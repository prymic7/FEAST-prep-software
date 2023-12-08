#include "STBimage.h"



STBimage::STBimage(std::string imagePath) : imagePath(imagePath), channels(0), width(0), height(0), m_RendererID(0), imageData(nullptr)
{


    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    stbi_set_flip_vertically_on_load(1);
    imageData = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);

    if (!imageData) {
        wxLogStatus("Wrong image path!"); //wxMessageBox, throw.. doesnt work wtf
    }

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D)); 

    if (imageData) {
        stbi_image_free(imageData);
    }
}

STBimage::~STBimage()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void STBimage::Bind(GLuint slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void STBimage::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}


