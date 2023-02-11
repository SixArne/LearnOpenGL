#include "pch.h"
#include "Texture.h"


Texture::Texture()
{}

Texture::Texture(std::string& fileLocation):
	m_FileLocation{fileLocation}
{}

Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture()
{
	auto textureData = stbi_load(m_FileLocation.c_str(), &m_Width, &m_Height, &m_BitDepth, 0);
	if (!textureData)
	{
		L_ERROR("Failed to find '{}'", m_FileLocation.c_str());
		return;
	}

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(textureData);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &m_TextureID);
	m_TextureID = 0;
	m_Width = 0;
	m_Height = 0;
	m_BitDepth = 0;
	m_FileLocation.clear();
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}