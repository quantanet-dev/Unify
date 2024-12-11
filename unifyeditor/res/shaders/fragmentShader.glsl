#version 330 core
layout (location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform vec4 uColor;
uniform sampler2D uTexture;
void main()
{
	vec4 texColor = texture(uTexture, v_TexCoords);
	color = texColor - (uColor / 8);
};