#include "pch.h"
#include <json/json.h>
#include "GLTFModel.h"
#include "Texture.h"
#include "VertexBufferObject.h"
#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Utils.h"

GLTFModel::GLTFModel(const char* file)
{
	ploadedtexname = new std::vector<std::string>();
	ploadedtex = new std::vector<Texture*>();
	std::string json_data = extract_file(file);
	if (json_data.empty())
	{
		load_failure = true;
		return;
	}
	json JSON = json::parse(json_data);
	GLTFModel::file = file;
	pdata = get_data(JSON);
	traverse_node(JSON, 0);
	delete pdata;
}

GLTFModel::~GLTFModel()
{
	handle_deletion(pvertices);
	handle_deletion(pindices);
	handle_vector_deletion(ptextures);
	handle_deletion(ploadedtexname);
	handle_deletion(ploadedtex);
}

void GLTFModel::draw
(
	ShaderProgram& shader,
	Camera& camera,
	graphics::vec3 translation,
	graphics::vec4 rotation,
	graphics::vec3 scale
)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Mesh::draw(shader, camera, matrices[i], translation, rotation, scale);
	}
}

std::string GLTFModel::extract_file(const char* path)
{
	std::string contents = "";
	std::ifstream file_input_stream;
	std::stringstream string_stream;
	try
	{
		file_input_stream.open(path, std::ios::binary);
		string_stream << file_input_stream.rdbuf();
		file_input_stream.close();
		contents = string_stream.str();
		return contents;
	}
	catch (const std::ifstream::failure& f)
	{
		std::cout << "Failure reading :: " << path << std::endl;
		std::cout << "Error :: " << f.what() << std::endl;
	}
	return contents;
}

void GLTFModel::load_mesh(json& JSON, unsigned int indMesh)
{
	unsigned int pos_acc_ind = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normal_acc_ind = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int tex_acc_ind = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int ind_acc_ind = JSON["meshes"][indMesh]["primitives"][0]["indices"];

	std::vector<float>* pposvec = get_floats(JSON["accessors"][pos_acc_ind], JSON);
	std::vector<graphics::vec3>* ppositions = group_floats_as_vec3(pposvec);
	std::vector<float>* pnormalvec = get_floats(JSON["accessors"][normal_acc_ind], JSON);
	std::vector<graphics::vec3>* pnormals = group_floats_as_vec3(pnormalvec);
	std::vector<float>* ptexvec = get_floats(JSON["accessors"][tex_acc_ind], JSON);
	std::vector<graphics::vec2>* ptexUVs = group_floats_as_vec2(ptexvec);

	pvertices = assemble_vertices(ppositions, pnormals, ptexUVs);
	pindices = get_indices(JSON["accessors"][ind_acc_ind], JSON);
	ptextures = get_textures(JSON);

	meshes.push_back(Mesh(pvertices, pindices, ptextures));

	delete pposvec;
	delete ppositions;
	delete pnormalvec;
	delete pnormals;
	delete ptexvec;
	delete ptexUVs;
}

void GLTFModel::traverse_node(json& JSON, unsigned int nextNode, graphics::mat4 matrix)
{
	json node = JSON["nodes"][nextNode];

	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float transValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
			transValues[i] = (node["translation"][i]);
		translation = glm::make_vec3(transValues);
	}

	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end())
	{
		float rotValues[4] =
		{
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};
		rotation = glm::make_quat(rotValues);
	}
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end())
	{
		float scaleValues[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++)
			scaleValues[i] = (node["scale"][i]);
		scale = glm::make_vec3(scaleValues);
	}

	glm::mat4 matNode = glm::mat4(1.0f);
	if (node.find("matrix") != node.end())
	{
		float matValues[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++)
			matValues[i] = (node["matrix"][i]);
		matNode = glm::make_mat4(matValues);
	}

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	glm::mat4 glmmatrix = to_glm_mat4(matrix);
	glm::mat4 matNextNode = glmmatrix * matNode * trans * rot * sca;

	if (node.find("mesh") != node.end())
	{
		translations.push_back(to_vect_vec3(translation));
		rotations.push_back(to_vect_vec4(rotation));
		scales.push_back(to_vect_vec3(scale));
		matrices.push_back(to_mat_mat4(matNextNode));
		load_mesh(JSON, node["mesh"]);
	}

	if (node.find("children") != node.end())
	{
		for (unsigned int i = 0; i < node["children"].size(); i++)
			traverse_node(JSON, node["children"][i], to_mat_mat4(matNextNode));
	}
}

std::vector<unsigned char>* GLTFModel::get_data(json& JSON)
{
	std::string bytesText;
	std::string uri = JSON["buffers"][0]["uri"];

	std::string fileStr = std::string(file);
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	bytesText = extract_file((fileDirectory + uri).c_str());

	pdata = new std::vector<unsigned char>(bytesText.begin(), bytesText.end());
	return pdata;
}

std::vector<float>* GLTFModel::get_floats(json& accessor, json& JSON)
{
	std::vector<float>* pfloatvec = new std::vector<float>();

	unsigned int buffViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int numPerVert;
	if (type == "SCALAR") numPerVert = 1;
	else if (type == "VEC2") numPerVert = 2;
	else if (type == "VEC3") numPerVert = 3;
	else if (type == "VEC4") numPerVert = 4;
	else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3 or VEC4)");

	unsigned int beginningOfData = byteOffset + accByteOffset;
	unsigned int lengthOfData = count * 4 * numPerVert;
	for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i)
	{
		unsigned char bytes[] = { (*pdata)[i++], (*pdata)[i++], (*pdata)[i++], (*pdata)[i++] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		pfloatvec->push_back(value);
	}
	return pfloatvec;
}

std::vector<GLuint>* GLTFModel::get_indices(json& accessor, json& JSON)
{
	std::vector<GLuint>* pindices = new std::vector<GLuint>();

	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int beginningOfData = byteOffset + accByteOffset;
	if (componentType == 5125)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
		{
			unsigned char bytes[] = { (*pdata)[i++], (*pdata)[i++], (*pdata)[i++], (*pdata)[i++] };
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			pindices->push_back((GLuint)value);
		}
	}
	else if (componentType == 5123)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
		{
			unsigned char bytes[] = { (*pdata)[i++], (*pdata)[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			pindices->push_back((GLuint)value);
		}
	}
	else if (componentType == 5122)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
		{
			unsigned char bytes[] = { (*pdata)[i++], (*pdata)[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof(short));
			pindices->push_back((GLuint)value);
		}
	}
	return pindices;
}

std::vector<Texture*>* GLTFModel::get_textures(json& JSON)
{
	std::vector<Texture*>* ptextures = new std::vector<Texture*>();

	std::string fileStr = std::string(file);
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

	for (unsigned int i = 0; i < JSON["images"].size(); i++)
	{
		std::string texPath = JSON["images"][i]["uri"];
		bool skip = false;
		for (unsigned int j = 0; j < ploadedtexname->size(); j++)
		{
			if ((*ploadedtexname)[j] == texPath)
			{
				ptextures->push_back((*ploadedtex)[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			if (texPath.find("baseColor") != std::string::npos || texPath.find("diffuse") != std::string::npos)
			{
				Texture* pdiffuse = new Texture((fileDirectory + texPath).c_str(), "diffuse", GL_TEXTURE0 + ploadedtex->size(), GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
				ptextures->push_back(pdiffuse);
				ploadedtex->push_back(pdiffuse);
				ploadedtexname->push_back(texPath);
			}
			else if (texPath.find("metallicRoughness") != std::string::npos || texPath.find("specular") != std::string::npos)
			{
				Texture* pspecular = new Texture((fileDirectory + texPath).c_str(), "specular", GL_TEXTURE0 + ploadedtex->size(), GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
				ptextures->push_back(pspecular);
				ploadedtex->push_back(pspecular);
				ploadedtexname->push_back(texPath);
			}
		}
	}
	return ptextures;
}

std::vector<Vertex>* GLTFModel::assemble_vertices
(
	std::vector<graphics::vec3>* ppositions,
	std::vector<graphics::vec3>* pnormals,
	std::vector<graphics::vec2>* ptextUVs
)
{
	std::vector<Vertex>* pvertices = new std::vector<Vertex>();;
	for (int i = 0; i < ppositions->size(); i++)
	{
		pvertices->push_back
		(
			Vertex
			{
				to_glm_vec3(ppositions->at(i)),
				to_glm_vec3(pnormals->at(i)),
				glm::vec3(1.0f, 1.0f, 1.0f),
				to_glm_vec2(ptextUVs->at(i))
			}
		);
	}
	return pvertices;
}

std::vector<graphics::vec2>* GLTFModel::group_floats_as_vec2(std::vector<float>* pfloatvec)
{
	std::vector<graphics::vec2>* pvectors = new std::vector<graphics::vec2>();
	for (int i = 0; i < pfloatvec->size(); i)
	{
		pvectors->push_back(graphics::vec2(pfloatvec->at(i++), pfloatvec->at(i++)));
	}
	return pvectors;
}

std::vector<graphics::vec3>* GLTFModel::group_floats_as_vec3(std::vector<float>* pfloatvec)
{
	std::vector<graphics::vec3>* pvectors = new std::vector<graphics::vec3>();
	for (int i = 0; i < pfloatvec->size(); i)
	{
		pvectors->push_back(graphics::vec3(pfloatvec->at(i++), pfloatvec->at(i++), pfloatvec->at(i++)));
	}
	return pvectors;
}

std::vector<graphics::vec4>* GLTFModel::group_floats_as_vec4(std::vector<float>* pfloatvec)
{
	std::vector<graphics::vec4>* pvectors = new std::vector<graphics::vec4>();
	for (int i = 0; i < pfloatvec->size(); i)
	{
		pvectors->push_back(graphics::vec4(pfloatvec->at(i++), pfloatvec->at(i++), pfloatvec->at(i++), pfloatvec->at(i++)));
	}
	return pvectors;
}

void GLTFModel::handle_deletion(void* p)
{
	if (p)
	{
		delete p;
	}
}

template<typename Type>
void GLTFModel::handle_vector_deletion(std::vector<Type*>* pvector)
{
	if (pvector)
	{
		for (int i = 0; i < pvector->size(); i++)
		{
			delete pvector->at(i);
		}
	}
	delete pvector;
}