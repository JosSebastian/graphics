#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in vec3 aNormal;

out vec3 Color;
out vec2 Texture;
out vec3 Normal;
out vec3 Position;

uniform mat4 Camera;
uniform mat4 Model;

void main()
{
	Position = vec3(Model * vec4(aPosition, 1.0));

	gl_Position = Camera * vec4(Position, 1.0);
	Color = aColor;
	Texture = aTexture;
	Normal = aNormal;
}