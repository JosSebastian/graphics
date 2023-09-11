#version 330 core

out vec4 Fragment;

uniform vec4 Light;

void main()
{
    Fragment = Light;
}