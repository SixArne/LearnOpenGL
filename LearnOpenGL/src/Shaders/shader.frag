#version 450 core

in vec4 vCol;
in vec2 vTexCoord0;

out vec4 fragColor;

struct DirectionalLight
{
	vec3 color;
	float ambientIntensity;
};

uniform sampler2D customTexture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

	fragColor = texture(customTexture, vTexCoord0) * ambientColor;
}