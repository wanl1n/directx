#include "Mesh.h"

#include "GraphicsEngine.h"
#include "VertexMesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <filesystem> 

void getCoordinates(tinyobj::attrib_t attribs, std::vector<tinyobj::shape_t> shapes, VertexBufferPtr* vb, IndexBufferPtr* ib);
void getCoordinatesWithTex(tinyobj::attrib_t attribs, std::vector<tinyobj::shape_t> shapes, VertexBufferPtr* vb, IndexBufferPtr* ib);

Mesh::Mesh(const wchar_t* path) : Resource(path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	auto inputfile = std::filesystem::path(path).string();

	bool loaded = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not loaded successfully.");
	if (!loaded) throw std::exception("Mesh not created successfully.");
	if (shapes.size() > 1) throw std::exception("More than 1 shape.");

	if (attribs.texcoords.size() > 0)
		getCoordinatesWithTex(attribs, shapes, &vb, &ib);
	else
		getCoordinates(attribs, shapes, &vb, &ib);
}

Mesh::~Mesh()
{
}

void getCoordinates(tinyobj::attrib_t attribs, std::vector<tinyobj::shape_t> shapes, VertexBufferPtr* vb, IndexBufferPtr* ib)
{
	std::vector<VertexMesh> vertices;
	std::vector<unsigned int> indices;

	/*for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
		indices.push_back(shapes[0].mesh.indices[i].vertex_index);
	}*/

	for (size_t s = 0; s < shapes.size(); s++) {
		for (size_t f = 0; f < shapes[s].mesh.indices.size(); f++) {
			tinyobj::index_t index = shapes[s].mesh.indices[f];

			tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
			tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
			tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

			tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
			tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
			tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];

			vertices.push_back({ Vector3(vx, vy, vz), Vector2(0), Vector3(nx, ny, nz) });
			indices.push_back(indices.size());
		}
	}

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shaderByteCode, &sizeShader);
	*vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertices, sizeof(VertexMesh), shaderByteCode, sizeShader);

	*ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&indices[0], (UINT)indices.size());
}

void getCoordinatesWithTex(tinyobj::attrib_t attribs, std::vector<tinyobj::shape_t> shapes, VertexBufferPtr* vb, IndexBufferPtr* ib)
{
	std::vector<VertexMesh> vertices;
	std::vector<unsigned int> indices;

	for (size_t s = 0; s < shapes.size(); s++) {
		size_t indexOffset = 0;
		vertices.reserve(shapes[s].mesh.indices.size());
		indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int faceVerts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < faceVerts; v++) {
				tinyobj::index_t index = shapes[s].mesh.indices[v + indexOffset];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tu = attribs.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t tv = attribs.texcoords[index.texcoord_index * 2 + 1];

				tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
				tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
				tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];

				Vector3 pos = Vector3(vx, vy, vz);
				Vector2 tex = Vector2(tu, tv);
				Vector3 normals = Vector3(nx, ny, nz);

				vertices.push_back({ pos, tex, normals });
				indices.push_back(v + indexOffset);
			}
			indexOffset += faceVerts;
		}
	}

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shaderByteCode, &sizeShader);
	*vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertices, sizeof(VertexMesh), shaderByteCode, sizeShader);

	*ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&indices[0], (UINT)indices.size());
}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
	return vb;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return ib;
}
