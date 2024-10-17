#include "Sphere.h"
#include <DirectXMath.h>

Sphere::Sphere(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, type, blending), rings(32), sectors(32), radius(1), color(WHITE)
{
	this->init();
}

Sphere::~Sphere() {}

void Sphere::initializeBuffers()
{
	std::vector<unsigned int> indices;

	// Precomputed values to optimize calculations
	float const ringStep = 1.0f / static_cast<float>(rings - 1);    // Step size for the rings
	float const sectorStep = 1.0f / static_cast<float>(sectors - 1); // Step size for the sectors

	int index = 0;
	for (unsigned int ring = 0; ring < rings - 1; ++ring)
	{
		for (unsigned int sector = 0; sector < sectors - 1; ++sector)
		{
			// Define two triangles for each quad on the sphere's surface
			// First triangle
			indices.push_back(ring * sectors + sector);
			indices.push_back((ring + 1) * sectors + sector);
			indices.push_back((ring + 1) * sectors + (sector + 1));

			// Second triangle
			indices.push_back(ring * sectors + sector);
			indices.push_back((ring + 1) * sectors + (sector + 1));
			indices.push_back(ring * sectors + (sector + 1));
		}
	}
	this->ib = GraphicsEngine::get()->createIndexBuffer();
	this->ib->load(indices);
}

std::vector<Vertex3D> Sphere::createVertices()
{
	std::vector<Vertex3D> vertices;

	// Default Values
	this->rings = 32.0f;
	this->sectors = 32.0f;
	this->color = WHITE;
	this->radius = 1.0f;

	// Precomputed values to optimize calculations
	float const ringStep = 1.0f / static_cast<float>(rings - 1);    // Step size for the rings
	float const sectorStep = 1.0f / static_cast<float>(sectors - 1); // Step size for the sectors
	
	for (unsigned int ring = 0; ring < rings; ++ring)
	{
		for (unsigned int sector = 0; sector < sectors; ++sector)
		{
			// Calculate the spherical coordinates for the vertex
			float const y = sinf(-DirectX::XM_PIDIV2 + DirectX::XM_PI * ring * ringStep); // Vertical (Y) position
			float const x = cosf(2 * DirectX::XM_PI * sector * sectorStep) * sinf(DirectX::XM_PI * ring * ringStep); // Horizontal (X) position
			float const z = sinf(2 * DirectX::XM_PI * sector * sectorStep) * sinf(DirectX::XM_PI * ring * ringStep); // Depth (Z) position

			// Create the vertex with position, normal, and texture coordinate
			Vertex3D vertex;
			vertex.position = Vector3(x * radius, y * radius, z * radius);
			vertex.color = WHITE;
			//vertex.normal = DirectX::XMFLOAT3(x, y, z); // Normal vector
			//vertex.texcoord = DirectX::XMFLOAT2(sector * sectorStep, ring * ringStep); // Texture coordinates

			// Store the vertex in the vertex buffer
			vertices.push_back(vertex);
		}
	}

	return vertices;
}
