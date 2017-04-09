
#version 330

uniform sampler2D sampler;

out vec4 colour;

in vec4 position;
in vec2 texture;

void main()
{
	colour = texture2D(sampler, texture);
}