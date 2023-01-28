#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLfloat GetBufferWidth() { return m_BufferWidth; };
	GLfloat GetBufferHeight() { return m_BufferHeight; };

	bool GetShouldClose() { return glfwWindowShouldClose(m_MainWindow); };
	void SwapBuffers() { glfwSwapBuffers(m_MainWindow); };

	~Window();

private:
	GLFWwindow* m_MainWindow{};
	GLint m_Width{};
	GLint m_Height{};
	GLint m_BufferWidth{};
	GLint m_BufferHeight{};
};


#endif
