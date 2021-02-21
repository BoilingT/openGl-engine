#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

//uniform vec3 transform;
uniform mat4 transform;

void main()
{
   gl_Position = vec4(aPos, 1.0f);
   ourColor = aColor; // set ourColor to the input color we got from the vertex data
   TexCoord = aTexCoord;
};