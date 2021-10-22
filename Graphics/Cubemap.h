#pragma once
#include "BaseHeader.h"

class Cubemap
{
	GLuint id;
	VertexArrayObject* pVAO;
	void load_cubemaps(std::vector<std::string>& paths);
	GLenum get_channel(int color_channel);
	std::vector<Vertex> get_vertices();
public:
	Cubemap(std::vector<std::string>& paths);
	~Cubemap();
	void draw(ShaderProgram& shader);
};