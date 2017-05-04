
#version 330

layout (location = 0) in vec4 vPosition;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

out vec2 texture;

void main() 
{
	vec4 position = vec4(vPosition.x, vPosition.y, 0.0, 1.0);
	vec2 texpos = vec2(vPosition.z, vPosition.w);
	
	gl_Position = Projection * View * Model * position;
	
	texture = texpos;
}