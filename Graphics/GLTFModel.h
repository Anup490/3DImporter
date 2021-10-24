#pragma once
#include "BaseHeader.h"
#include "BaseModel.h"
#include "Matrix.h"

namespace nlohmann
{
	template<typename, typename>
	struct adl_serializer;

	template<template<typename U, typename V, typename... Args> class ObjectType =
		std::map,
		template<typename U, typename... Args> class ArrayType = std::vector,
		class StringType = std::string, class BooleanType = bool,
		class NumberIntegerType = std::int64_t,
		class NumberUnsignedType = std::uint64_t,
		class NumberFloatType = double,
		template<typename U> class AllocatorType = std::allocator,
		template<typename T, typename SFINAE = void> class JSONSerializer =
		adl_serializer,
		class BinaryType = std::vector<std::uint8_t>>
		class basic_json;
	using json = basic_json<>;
}
using json = nlohmann::json;

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
		vect::vec3 translation = vect::vec3(0.0f, 0.0f, 0.0f),
		vect::vec4 rotation = vect::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		vect::vec3 scale = vect::vec3(1.0f, 1.0f, 1.0f)
	) override;
private:
	const char* file;
	std::vector<unsigned char>* pdata;

	std::vector<Mesh> meshes;
	std::vector<vect::vec3> translations;
	std::vector<vect::vec4> rotations;
	std::vector<vect::vec3> scales;
	std::vector<mat::mat4> matrices;

	std::vector<std::string>* ploadedtexname;
	std::vector<Texture*>* ploadedtex;
	std::vector<Vertex>* pvertices;
	std::vector<GLuint>* pindices;
	std::vector<Texture*>* ptextures;

	std::string extract_file(const char* path);
	void load_mesh(json& JSON, unsigned int indMesh);
	void traverse_node(json& JSON, unsigned int nextNode, mat::mat4 matrix = mat::mat4(1.0f));
	std::vector<unsigned char>* get_data(json& JSON);

	std::vector<float>* get_floats(json& accessor, json& JSON);
	std::vector<GLuint>* get_indices(json& accessor, json& JSON);
	std::vector<Texture*>* get_textures(json& JSON);

	std::vector<Vertex>* assemble_vertices
	(
		std::vector<vect::vec3>* ppositions,
		std::vector<vect::vec3>* pnormals,
		std::vector<vect::vec2>* ptextUVs
	);

	std::vector<vect::vec2>* group_floats_as_vec2(std::vector<float>* pfloatvec);
	std::vector<vect::vec3>* group_floats_as_vec3(std::vector<float>* pfloatvec);
	std::vector<vect::vec4>* group_floats_as_vec4(std::vector<float>* pfloatvec);
};