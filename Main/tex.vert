#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;
out vec3 color;
out vec2 texCoord;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	//OpenGL uses column major order in matrix
	texCoord = mat2(1.0, 0.0, 0.0, -1.0) * aTexCoord;
	color = aColor;
}