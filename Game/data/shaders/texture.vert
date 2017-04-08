
#version 330

layout (location = 0) in vec4 vPosition;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

out vec2 texture;

void main() 
{
	vec4 ActualPosition = vec4(vPosition.xy, 0.0, 1.0);
	mat4 ModelView = View * Model;
	gl_Position = Projection * ModelView * ActualPosition;
	texture = vPosition.zw;
}