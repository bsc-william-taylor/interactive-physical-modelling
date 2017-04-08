

#version 330

uniform sampler2D sampler;
uniform vec4 text_colour;

out vec4 colour;

in vec2 texture;

void main()
{
	colour = texture2D(sampler, texture) * text_colour;
}