#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(glm::vec3& color, GLfloat intensity);

	~Light() = default;

	virtual void UseLight(GLint intensityLocation, GLint colorLocation);

private:
	glm::vec3 m_Color{};
	GLfloat m_AmbientIntensity{};
};

#endif