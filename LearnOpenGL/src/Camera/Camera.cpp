#include "pch.h"
#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) : 
	m_Position{ startPosition },
	m_WorldUp{ startUp },
	m_Yaw{ startYaw },
	m_Pitch{ startPitch },
	m_Front{glm::vec3(0.0f, 0.0f, -1.0f)},
	m_MovementSpeed{startMoveSpeed},
	m_TurnSpeed{startTurnSpeed}
{
	Update();
}

Camera::Camera(CameraCreateInfo& info) :
	Camera::Camera(
		info.startPosition,
		info.startUp,
		info.startYaw,
		info.startPitch,
		info.startMoveSpeed,
		info.startTurnSpeed
	)
{}

void Camera::Update()
{
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Front = glm::normalize(m_Front);

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}


void Camera::KeyControl(std::array<bool, 1024>& keys, float deltaTime)
{
	const float velocity = m_MovementSpeed * deltaTime;

	// Forward / backwards
	if (keys[GLFW_KEY_W])
	{
		m_Position += m_Front * velocity;
	}
	else if (keys[GLFW_KEY_S])
	{
		m_Position -= m_Front * velocity;
	}

	// Left / right
	if (keys[GLFW_KEY_D])
	{
		m_Position += m_Right * velocity;
	}
	else if (keys[GLFW_KEY_A])
	{
		m_Position -= m_Right * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= m_TurnSpeed;
	yChange *= m_TurnSpeed;

	m_Yaw += xChange;
	m_Pitch += yChange;

	if (m_Pitch > 89.0f)
	{
		m_Pitch = 89.0f;
	}

	if (m_Pitch < -89.0f)
	{
		m_Pitch = -89.0f;
	}

	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

Camera::~Camera()
{

}