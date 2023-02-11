#include "pch.h"
#include "Light.h"

Light::Light()
	: m_Color{ glm::vec3(1.0, 1.0f, 1.0f) }, m_AmbientIntensity{1.0f}
{}

Light::Light(glm::vec3& color, GLfloat intensity)
	: m_Color{ color }, m_AmbientIntensity{ intensity }
{}

void Light::UseLight(GLint intensityLocation, GLint colorLocation)
{
	glUniform3f(colorLocation, m_Color.r, m_Color.g, m_Color.b);
	glUniform1f(intensityLocation, m_AmbientIntensity);
}