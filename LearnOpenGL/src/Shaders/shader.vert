#version 450 core

layout (location = 0) in vec3 pos;

uniform float xMove;

void main()
{
	gl_Position = vec4(pos.x + xMove, pos.y, pos.z, 1.0);
}