#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 color;
uniform sampler2D diffuse;
uniform sampler2D specular;
void main()
{
	FragColor = mix(texture(diffuse, texCoord),texture(specular, texCoord), 0.5f);
}