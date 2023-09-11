#version 330 core

out vec4 Fragment;

uniform vec4 LightColor;

void main()
{
    Fragment = LightColor;
}