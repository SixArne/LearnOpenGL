#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <STB_IMAGE/stb_image.h>

class Texture
{
public:
	Texture();
	Texture(std::string& fileLocation);
	~Texture();

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

private:
	GLuint m_TextureID{};
	int m_Width{};
	int m_Height{};
	int m_BitDepth{};

	std::string m_FileLocation{};
};


#endif
