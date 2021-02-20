#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

//uniform vec3 transform;
uniform mat4 transform;

void main()
{
   gl_Position = transform * vec4(aPos, 1.0f);
   ourColor = aColor; // set ourColor to the input color we got from the vertex data
};