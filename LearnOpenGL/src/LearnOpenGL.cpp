#include "pch.h"
#include <iostream>

#include <VLD/vld.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO{}, VBO{}, shader{}, uniformXMove{};

bool direction = true;
float triOffset = 0.f;
float triMaxOffset = .7f;
float triIncrement = 0.0005f;

std::string ReadShaderFile(const std::string& src)
{
	std::fstream file{src};
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

void AddShader(GLuint program, std::string& code, GLenum type)
{
	const GLint mainShader = glCreateShader(type);

	const std::array<GLchar*, 1> shaderCode{
		code.data()
	};

	const std::array<GLint, 1> codeLength{
		static_cast<GLint>(code.size()),
	};

	glShaderSource(mainShader, 1, shaderCode.data(), codeLength.data());
	glCompileShader(mainShader);

	GLint result{};
	std::array<GLchar, 1024> log{0};
	glGetShaderiv(mainShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(mainShader, sizeof(log), nullptr, log.data());
		std::printf("Error compiling the %d shader '%s'\n", type, log.data());

		__debugbreak();
	}

	glAttachShader(program, mainShader);
}

void CompileShader()
{
	shader = glCreateProgram();

	// check if shader is valid
	ASSERT(shader)

	if (!shader)	
	{
		__debugbreak();
	}

	// Get shader files into string format
	auto vertShader = ReadShaderFile("./src/Shaders/shader.vert");
	auto fragShader = ReadShaderFile("./src/Shaders/shader.frag");

	// Add shaders to program
	AddShader(shader, vertShader, GL_VERTEX_SHADER);
	AddShader(shader, fragShader, GL_FRAGMENT_SHADER);

	GLint result{0};
	std::array<GLchar, 1024> log{0};

	// Linking stage
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(log), nullptr, log.data());
		std::printf("Error linking program '%s'\n", log.data());

		__debugbreak();
	}

	// Validation stage
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(log), nullptr, log.data());
		std::printf("Error validating program '%s'\n", log.data());

		__debugbreak();
	}

	uniformXMove = glGetUniformLocation(shader, "xMove");
}

void CreateTriangle()
{
	const std::array<GLfloat, 9> vertices
	{
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		0.f, 1.f, 0.f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

int main()
{
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();

		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow{ glfwCreateWindow(WIDTH, HEIGHT, "Test window", nullptr, nullptr) };

	ASSERT(mainWindow);

	int bufferWidth{}, bufferHeight{};
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;

	ASSERT(glewInit() == GLEW_OK)

	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShader();

	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (std::abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glUniform1f(uniformXMove, triOffset);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}