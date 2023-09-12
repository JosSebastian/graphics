#version 330 core

out vec4 Fragment;

in vec3 Color;
in vec2 Texture;
in vec3 Normal;
in vec3 Position;

uniform sampler2D Sampler;

uniform vec4 LightColor;
uniform vec3 LightPosition;

uniform vec3 CameraPosition;

void main()
{

	float Ambient = 0.30f;

	vec3 Normals = normalize(Normal);
	vec3 Direction = normalize(LightPosition - Position);

	float Diffuse = max(dot(Normals, Direction), 0.0);

	float Light = 0.5f;
	vec3 View = normalize(CameraPosition - Position);   
	vec3 Reflection = reflect(-Direction, Normals);
	float Amount = pow(max(dot(View, Reflection), 0.0f), 8);
	float Specular = Light * Amount;

	Fragment = texture(Sampler, Texture) * LightColor * (Diffuse + Ambient + Specular);
}