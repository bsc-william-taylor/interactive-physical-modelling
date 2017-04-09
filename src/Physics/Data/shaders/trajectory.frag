
#version 330 core

out vec4 colour;

in vec4 currentPoint;
in vec4 startPoint;

void main()
{
	if(currentPoint.x <= startPoint.x)
	{
		colour = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else
	{
		colour = vec4(0.0, 0.0, 1.0, 1.0);
	}
}