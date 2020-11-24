#include "Texture.h"
#include <stb_image.h>

Texture::Texture(const std::string& path, GLuint texID)
{
    filePath = path;
    this->texID = texID;

    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

    glGenTextures(1, &rendererID);
    //glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
    glBindTexture(GL_TEXTURE_2D, rendererID);

    /* glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
     glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    //glGenerateMipmap(GL_TEXTURE_2D);

    Unbind();

    if (localBuffer) {
        stbi_image_free(localBuffer);
        localBuffer = nullptr;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &rendererID);
}

void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0 + this->texID);
	glBindTexture(GL_TEXTURE_2D, rendererID);
	//glBindTextureUnit(this->texID, rendererID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Texture::GetFilePath() const
{
    return filePath;
}

GLint Texture::GetWidth() const
{
    return width;
}

GLint Texture::GetHeight() const
{
    return height;
}

GLint Texture::GetBPP() const
{
    return BPP;
}


GLuint Texture::GetTexID() const
{
    return texID;
}

GLuint Texture::GetRendererID() const
{
    return rendererID;
}

