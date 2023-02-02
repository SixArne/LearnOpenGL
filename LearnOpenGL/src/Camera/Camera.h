#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	struct CameraCreateInfo
	{
		glm::vec3 startPosition;
		glm::vec3 startUp;
		GLfloat startYaw;
		GLfloat startPitch;
		GLfloat startMoveSpeed;
		GLfloat startTurnSpeed;
	};

	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	Camera(CameraCreateInfo& cameraCreateInfo);

	void KeyControl(std::array<bool, 1024>& keys, float deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);
	glm::mat4 CalculateViewMatrix();

	~Camera();

private:
	glm::vec3 m_Position{};
	glm::vec3 m_Front{};
	glm::vec3 m_Up{};
	glm::vec3 m_Right{};
	glm::vec3 m_WorldUp{0,1,0};

	GLfloat m_Yaw{};
	GLfloat m_Pitch{};

	GLfloat m_MovementSpeed{};
	GLfloat m_TurnSpeed{};

	void Update();
};


#endif