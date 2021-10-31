#pragma once
#include "BaseHeader.h"

class Window;
class Cubemap
{
	GLuint id;
	std::vector<Vertex>* pvertices;
	VertexArrayObject* pVAO;
	void load_cubemaps(std::vector<std::string>& paths);
	GLenum get_channel(int color_channel);
	void prepare_vertices();
public:
	Cubemap(std::vector<std::string>& paths);
	~Cubemap();
	void draw(ShaderProgram& shader, Window& window);
};