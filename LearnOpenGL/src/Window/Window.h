#ifndef WINDOW_H
#define WINDOW_H

#include "pch.h"
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

	// reference to key list
	std::array<bool, 1024>& GetKeys() { return m_Keys; };
	GLfloat GetXChange();
	GLfloat GetYChange();

	GLFWwindow* GetWindow() { return m_MainWindow; };
	bool IsFocussed() { return m_IsFocussed; };

	~Window();

private:
	GLFWwindow* m_MainWindow{};
	GLint m_Width{};
	GLint m_Height{};
	GLint m_BufferWidth{};
	GLint m_BufferHeight{};
	
	// keyboard
	std::array<bool, 1024> m_Keys{false};
	
	// mouse
	GLfloat m_LastX{};
	GLfloat m_LastY{};
	GLfloat m_XChange{};
	GLfloat m_YChange{};
	bool m_MouseFirstMoved{true};
	bool m_IsFocussed{ true };

	// Event callbacks
	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};


#endif
