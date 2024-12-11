#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

uniform mat4 uMVP;

void main()
{
   gl_Position = position * uMVP;
   v_TexCoords = texCoords;
};