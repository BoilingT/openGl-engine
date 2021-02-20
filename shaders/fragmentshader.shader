#version 330 core
out vec4 FragColor;
in vec4 vertexColor;

uniform vec4 ourColor; //This variable will be set in the opengl code.

void main()
{
	FragColor = ourColor;
};