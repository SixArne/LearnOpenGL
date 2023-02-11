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
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();

	void UseShader();
	void ClearShader();

private:
	GLuint m_ShaderID{};
	GLuint m_UniformProjection{};
	GLuint m_UniformModel{};
	GLuint m_UniformView{};
	GLuint m_UniformAmbientIntensity{};
	GLuint m_UniformAmbientColor{};

	void CompileShader(const std::string& vertexCode, const std::string& fragmentCode);
	void AddShader(GLuint program, const std::string& code, GLenum type);
	std::string ReadFromFile(const std::string& filelocation);
};


#endif



