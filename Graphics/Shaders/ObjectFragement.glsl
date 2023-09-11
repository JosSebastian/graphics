#version 330 core

out vec4 Fragment;

in vec3 Color;
in vec2 Texture;
in vec3 Normal;
in vec3 Position;

uniform sampler2D Sampler;

uniform vec4 LightColor;
uniform vec3 LightPosition;

void main()
{

	float Ambient = 0.30f;

	vec3 Normals = normalize(Normal);
	vec3 Direction = normalize(LightPosition - Position);

	float Diffuse = max(dot(Normals, Direction), 0.0);

	Fragment = texture(Sampler, Texture) * LightColor * (Diffuse + Ambient);
}