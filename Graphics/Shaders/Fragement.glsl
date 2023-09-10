#version 330 core

out vec4 Fragment;

in vec3 Color;
in vec2 Texture;

uniform sampler2D USampler;

void main()
{
	Fragment = texture(USampler, Texture);
}