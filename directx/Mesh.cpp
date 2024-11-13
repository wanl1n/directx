#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <filesystem> 

#include "GraphicsEngine.h"
#include "VertexMesh.h"

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

				Vector3 pos = Vector3(vx, vy, vz);
				Vector2 tex = Vector2(tu, tv);
				vertices.push_back({pos, tex});
				indices.push_back(v + indexOffset);
			}
			indexOffset += faceVerts;
		}
	}

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shaderByteCode, &sizeShader);
	vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertices, sizeof(VertexMesh), shaderByteCode, sizeShader);
	
	ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&indices[0], (UINT)indices.size());
}

Mesh::~Mesh()
{
}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
	return vb;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return ib;
}
