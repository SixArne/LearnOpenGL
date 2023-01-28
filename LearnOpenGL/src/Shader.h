#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();


	void CreateFromString(const std::string& vertFile, const std::string& fragFile);
	void CreateFromFiles(const std::string& vertFileLocation, const std::string& fragFileLocation);
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	void UseShader();
	void ClearShader();

private:
	GLuint m_ShaderID{};
	GLuint m_UniformProjection{};
	GLuint m_UniformModel{};

	void CompileShader(const std::string& vertexCode, const std::string& fragmentCode);
	void AddShader(GLuint program, const std::string& code, GLenum type);
	std::string ReadFromFile(const std::string& filelocation);
};


#endif



