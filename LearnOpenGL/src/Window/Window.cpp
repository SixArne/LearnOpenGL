#include "pch.h"
#include "Window.h"

Window::Window()
    : m_Width{800}, m_Height{600}
{
}

Window::Window(GLint windowWidth, GLint windowHeight)
    : m_Width{ windowWidth }, m_Height{windowHeight}
{
}

int Window::Initialize()
{
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();

		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_MainWindow =  glfwCreateWindow(m_Width, m_Height, "Test window", nullptr, nullptr);

	ASSERT(m_MainWindow);

	glfwGetFramebufferSize(m_MainWindow, &m_BufferWidth, &m_BufferHeight);

	glfwMakeContextCurrent(m_MainWindow);

	glewExperimental = GL_TRUE;

	ASSERT(glewInit() == GLEW_OK)

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, m_BufferWidth, m_BufferHeight);
}

Window::~Window()
{
	glfwDestroyWindow(m_MainWindow);
	glfwTerminate();
}
