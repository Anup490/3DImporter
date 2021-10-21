#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 color;
uniform sampler2D diffuse;
void main()
{
	FragColor = texture(diffuse, texCoord);
}