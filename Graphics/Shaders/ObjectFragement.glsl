#version 330 core

out vec4 Fragment;

in vec3 Color;
in vec2 Texture;

uniform sampler2D Sampler;
uniform vec4 Light;

void main()
{
	Fragment = texture(Sampler, Texture) * Light;
}