#include "pch.h"
#include "Shader.h"

Shader::Shader()
	:m_ShaderID{}, m_UniformModel{}, m_UniformProjection{}, m_UniformView{}
{}

Shader::~Shader()
{
	ClearShader();
}

void Shader::CreateFromFiles(const std::string& vertCodeLocation, const std::string& fragCodeLocation)
{
	const auto vertCode = ReadFromFile(vertCodeLocation);
	const auto fragCode = ReadFromFile(fragCodeLocation);

	CompileShader(vertCode, fragCode);
}

void Shader::CreateFromString(const std::string& vertCode, const std::string& fragCode)
{
	CompileShader(vertCode, fragCode);
}

std::string Shader::ReadFromFile(const std::string& filelocation)
{
	std::fstream file{ filelocation };
	std::string fileContent{};

	if (file.is_open())
	{
		fileContent.assign(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>()
		);
	}
	else
	{
		throw std::runtime_error("Failed to read shader file");
	}

	return fileContent;
}

GLuint Shader::GetProjectionLocation()
{
	return m_UniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return m_UniformModel;
}

GLuint Shader::GetViewLocation()
{
	return m_UniformView;
}

void Shader::UseShader()
{
	glUseProgram(m_ShaderID);
}

void Shader::ClearShader()
{
	if (m_ShaderID != 0)
	{
		glDeleteProgram(m_ShaderID);
		m_ShaderID = 0;
	}

	m_UniformModel = 0;
	m_UniformProjection = 0;
}

void Shader::CompileShader(const std::string& vertexCode, const std::string& fragmentCode)
{
	m_ShaderID = glCreateProgram();

	// check if shader is valid
	ASSERT(m_ShaderID)

	// Add shaders to program
	AddShader(m_ShaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(m_ShaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result{ 0 };
	std::array<GLchar, 1024> log{ 0 };

	// Linking stage
	glLinkProgram(m_ShaderID);
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_ShaderID, sizeof(log), nullptr, log.data());
		std::printf("Error linking program '%s'\n", log.data());

		__debugbreak();
	}

	// Validation stage
	glValidateProgram(m_ShaderID);
	glGetProgramiv(m_ShaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_ShaderID, sizeof(log), nullptr, log.data());
		std::printf("Error validating program '%s'\n", log.data());

		__debugbreak();
	}

	// Get uniform properties from shader
	m_UniformModel = glGetUniformLocation(m_ShaderID, "model");
	m_UniformProjection = glGetUniformLocation(m_ShaderID, "projection");
	m_UniformView = glGetUniformLocation(m_ShaderID, "view");
}

void Shader::AddShader(GLuint program, const std::string& code, GLenum type)
{
	const GLint mainShader = glCreateShader(type);

	const std::array<const GLchar*, 1> shaderCode{
		code.data()
	};

	const std::array<GLint, 1> codeLength{
		static_cast<GLint>(code.size()),
	};

	glShaderSource(mainShader, 1, shaderCode.data(), codeLength.data());
	glCompileShader(mainShader);

	GLint result{};
	std::array<GLchar, 1024> log{ 0 };
	glGetShaderiv(mainShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(mainShader, sizeof(log), nullptr, log.data());
		std::printf("Error compiling the %d shader '%s'\n", type, log.data());

		__debugbreak();
	}

	glAttachShader(program, mainShader);
}


