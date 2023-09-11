#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;


out vec3 Color;
out vec2 Texture;

uniform mat4 Camera;

void main()
{
	gl_Position = Camera * vec4(aPosition, 1.0);
	Color = aColor;
	Texture = aTexture;
}