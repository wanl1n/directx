#include "Capsule.h"
#include <DirectXMath.h>

Capsule::Capsule(std::string name, bool blending, OBJECT_TYPE type) :
    Primitive(name, type, blending), 
	height(1.0f), rings(32), sectors(32), radius(0.5f), color(WHITE)
{
	// Default Values
	this->rings = 32;
	this->sectors = 32;
	this->radius = 0.5f;
	this->height = 1.0f;
	this->color = WHITE;

    this->init();

	this->setPosition(Math::Vector3(-1, -1, 0));
	//this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Logo.jpg");
}

Capsule::~Capsule() {}

void Capsule::initializeBuffers()
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
    this->ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indices);
}

std::vector<Vertex3D> Capsule::createVertices()
{
	Math::Vector2 uvs[] = {
		Math::Vector2(0, 0),
		Math::Vector2(0, 1),
		Math::Vector2(1, 0),
		Math::Vector2(1, 1)
	};

	std::vector<Vertex3D> vertices;
	// Precomputed values to optimize calculations
	float ringStep = 1.0f / (float)(rings - 1);    // Step size for the rings
	float sectorStep = 1.0f / (float)(sectors - 1); // Step size for the sectors
	float half = (float)rings / 2;

	for (int ring = 0; ring < rings; ++ring)
	{
		for (unsigned int sector = 0; sector < sectors; ++sector)
		{
			// Calculate the spherical coordinates for the vertex
			float y = sinf(-DirectX::XM_PIDIV2 + DirectX::XM_PI * ring * ringStep); // Vertical (Y) position
			float x = cosf(2 * DirectX::XM_PI * sector * sectorStep) * sinf(DirectX::XM_PI * ring * ringStep); // Horizontal (X) position
			float z = sinf(2 * DirectX::XM_PI * sector * sectorStep) * sinf(DirectX::XM_PI * ring * ringStep); // Depth (Z) position

			if (ring > half)
				y += height;
			else
				y -= height;

			if (sector % 2 == 0)
				color = COUNTRYCORK;
			else
				color = LIGHTMAUVE;

			Math::Vector2 uv = Math::Vector2(0, 0);
			if (sector % 2 == 0)
				uv = Math::Vector2(0, 0);
			else
				uv = Math::Vector2(1, 1);

			// Create the vertex with position, normal, and texture coordinate
			Vertex3D vertex = {
				Math::Vector3(x * radius, y * radius, z * radius),
				uv,
				color
			};

			// Store the vertex in the vertex buffer
			vertices.push_back(vertex);
		}
	}

	return vertices;
}