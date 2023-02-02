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

	// Will break if error was discovered [DEBUG ONLY]
	ASSERT(m_MainWindow);

	glfwGetFramebufferSize(m_MainWindow, &m_BufferWidth, &m_BufferHeight);

	glfwMakeContextCurrent(m_MainWindow);
	
	// Set event callbacks
	CreateCallbacks();

	// Lock mouse
	glfwSetInputMode(m_MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	// Will break if error was discovered [DEBUG ONLY]
	ASSERT(glewInit() == GLEW_OK)

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, m_BufferWidth, m_BufferHeight);

	// attach current window data to window.
	glfwSetWindowUserPointer(m_MainWindow, this);

	return 0;
}

Window::~Window()
{
	glfwDestroyWindow(m_MainWindow);
	glfwTerminate();
}

void Window::CreateCallbacks()
{
	glfwSetKeyCallback(m_MainWindow, HandleKeys);
	glfwSetCursorPosCallback(m_MainWindow, HandleMouse);
}

GLfloat Window::GetXChange()
{
	GLfloat change = m_XChange;
	m_XChange = 0.f;

	return change;
}

GLfloat Window::GetYChange()
{
	GLfloat change = m_YChange;
	m_YChange = 0.f;

	return change;
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE)
	{
		if (thisWindow->m_IsFocussed)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			thisWindow->m_IsFocussed = false;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			thisWindow->m_IsFocussed = true;
		}
	}

	// If valid key
	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
		{
			thisWindow->m_Keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			thisWindow->m_Keys[key] = false;
		}
	}
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (thisWindow->m_MouseFirstMoved)
	{
		thisWindow->m_LastX = xPos;
		thisWindow->m_LastY = yPos;

		thisWindow->m_MouseFirstMoved = false;
	}

	thisWindow->m_XChange = xPos - thisWindow->m_LastX;
	thisWindow->m_YChange = thisWindow->m_LastY - yPos;

	thisWindow->m_LastX = xPos;
	thisWindow->m_LastY = yPos;
	
	L_DEBUG("[DELTA] X: {}, [DELTA] Y: {}", thisWindow->m_XChange, thisWindow->m_YChange);
}