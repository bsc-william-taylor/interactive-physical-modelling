
#version 330 core

layout (location = 0) in vec2 positions;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;
uniform vec2 Start;

out vec4 currentPoint;
out vec4 startPoint;

void main()
{
	mat4 Matrix = Projection * (View * Model);

	gl_Position = Matrix * vec4(positions.xy, 0.0, 1.0);

	currentPoint = Matrix * vec4(positions.xy, 0.0, 1.0);
	startPoint =  Matrix * vec4(Start, 0.0, 1.0);
}