#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 TexCoords;
uniform mat4 view;
void main()
{
	//Here, the inverse of view matrix is required. But as the view matrix is an orthogonal matrix, its inverse will be same as transpose.
	//And the reason why transpose is used here is because calculating transpose is much faster than calculating inverse.
   TexCoords = vec3(transpose(view) * vec4(aPos, 1.0));
   gl_Position = vec4(aPos, 1.0);
}