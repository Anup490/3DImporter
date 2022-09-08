#pragma once
#include "BaseHeader.h"
#include "BaseModel.h"
#include "Matrix.h"

class Mesh;

class GLTFModel : public BaseModel
{
public:
	GLTFModel(const char* file);
	~GLTFModel();
	void draw
	(
		ShaderProgram& shader,
		Camera& camera,
		graphics::vec3 translation = graphics::vec3(0.0f, 0.0f, 0.0f),
		graphics::vec4 rotation = graphics::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		graphics::vec3 scale = graphics::vec3(1.0f, 1.0f, 1.0f)
	) override;
	bool has_failed();
private:
	class GLTFModelImpl* pimpl;
	/*const char* file;
	std::vector<unsigned char>* pdata;

	std::vector<Mesh> meshes;
	std::vector<graphics::vec3> translations;
	std::vector<graphics::vec4> rotations;
	std::vector<graphics::vec3> scales;
	std::vector<graphics::mat4> matrices;

	std::vector<std::string>* ploadedtexname;
	std::vector<Texture*>* ploadedtex;
	std::vector<Vertex>* pvertices;
	std::vector<GLuint>* pindices;
	std::vector<Texture*>* ptextures;

	std::string extract_file(const char* path);
	void load_mesh(json& JSON, unsigned int indMesh);
	void traverse_node(json& JSON, unsigned int nextNode, graphics::mat4 matrix = graphics::mat4(1.0f));
	std::vector<unsigned char>* get_data(json& JSON);

	std::vector<float>* get_floats(json& accessor, json& JSON);
	std::vector<GLuint>* get_indices(json& accessor, json& JSON);
	std::vector<Texture*>* get_textures(json& JSON);

	std::vector<Vertex>* assemble_vertices
	(
		std::vector<graphics::vec3>* ppositions,
		std::vector<graphics::vec3>* pnormals,
		std::vector<graphics::vec2>* ptextUVs
	);

	std::vector<graphics::vec2>* group_floats_as_vec2(std::vector<float>* pfloatvec);
	std::vector<graphics::vec3>* group_floats_as_vec3(std::vector<float>* pfloatvec);
	std::vector<graphics::vec4>* group_floats_as_vec4(std::vector<float>* pfloatvec);
	void handle_deletion(void* pointer);
	template<typename Type> void handle_vector_deletion(std::vector<Type*>* pvector);*/
};