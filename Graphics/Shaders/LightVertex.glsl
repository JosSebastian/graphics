#version 330 core

layout (location = 0) in vec3 aPosition;

uniform mat4 Model;
uniform mat4 Camera;

void main()
{
	gl_Position = Camera * Model * vec4(aPosition, 1.0);
}