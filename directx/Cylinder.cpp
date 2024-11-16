#include "Cylinder.h"
#include <DirectXMath.h>

Cylinder::Cylinder(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, type, blending), height(2), slices(32), radius(1), stacks(1), color(WHITE)
{
    this->height = 2.0f;
    this->slices = 32.0f;
    this->radius = 1.0f;
    this->stacks = 1.0f;
    this->color = WHITE;

	this->init();

    this->setPosition(Math::Vector3(-5, 1.1f, 5));
    //this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Logo.jpg");
}

Cylinder::~Cylinder() {}

void Cylinder::initializeBuffers()
{
	std::vector<unsigned int> indices;

    // Generate indices for the top cap
    int topCenterIndex = 0;
    for (int i = 1; i <= slices; ++i)
    {
        int nextIndex = (i % slices) + 1;
        indices.push_back(topCenterIndex);  // Center of the top cap
        indices.push_back(nextIndex);       // Next vertex on the circle
        indices.push_back(i);               // Current vertex on the circle
    }

    // Generate indices for the bottom cap
    unsigned int bottomCenterIndex = slices + 1;
    for (unsigned int i = 0; i < slices; ++i)
    {
        unsigned int currentVertexIndex = bottomCenterIndex + 1 + i;
        unsigned int nextVertexIndex = bottomCenterIndex + 1 + ((i + 1) % slices);

        indices.push_back(bottomCenterIndex);      // Center of the bottom cap
        indices.push_back(currentVertexIndex);     // Current vertex on the circle
        indices.push_back(nextVertexIndex);        // Next vertex on the circle
    }

    // Generate indices for the side walls
    int sideStartIndex = bottomCenterIndex + slices + 1;
    for (int i = 0; i < slices; ++i)
    {
        int topIndex = sideStartIndex + i * 2;
        int bottomIndex = topIndex + 1;
        int nextTopIndex = sideStartIndex + ((i + 1) % slices) * 2;
        int nextBottomIndex = nextTopIndex + 1;

        // First triangle for the side
        indices.push_back(topIndex);
        indices.push_back(nextTopIndex);
        indices.push_back(bottomIndex);

        // Second triangle for the side
        indices.push_back(bottomIndex);
        indices.push_back(nextTopIndex);
        indices.push_back(nextBottomIndex);
    }
	this->ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indices);
}

std::vector<Vertex3D> Cylinder::createVertices()
{
	std::vector<Vertex3D> vertices;

    float halfHeight = height / 2.0f;
    float sliceStep = 2 * DirectX::XM_PI / static_cast<float>(slices);

    // Generate vertices for the top cap
    Vertex3D topCenter = { Math::Vector3(0.0f, halfHeight, 0.0f), Math::Vector2(0.5f, 0.5f), this->color };
    //Vertex3D topCenter = { Math::Vector3(0.0f, halfHeight, 0.0f), Math::Vector3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f) };
    vertices.push_back(topCenter);

    for (unsigned int i = 0; i < slices; ++i)
    {
        float theta = i * sliceStep;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        Math::Vector2 uv = Math::Vector2((x / radius + 1) * 0.5f, (z / radius + 1) * 0.5f);
        Vertex3D topVertex = { Math::Vector3(x, halfHeight, z), uv, this->color };
        //Vertex3D topVertex = { Math::Vector3(x, halfHeight, z), Math::Vector3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2((x / radius + 1) * 0.5f, (z / radius + 1) * 0.5f) };
        vertices.push_back(topVertex);
    }

    // Generate vertices for the bottom cap
    Vertex3D bottomCenter = { Math::Vector3(0.0f, -halfHeight, 0.0f), Math::Vector2(0.5f, 0.5f) };
    //Vertex bottomCenter = { Math::Vector3(0.0f, -halfHeight, 0.0f), Math::Vector3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.5f, 0.5f) };
    vertices.push_back(bottomCenter);

    for (unsigned int i = 0; i < slices; ++i)
    {
        float theta = i * sliceStep;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        Math::Vector2 uv = Math::Vector2((x / radius + 1) * 0.5f, (z / radius + 1) * 0.5f);
        Vertex3D bottomVertex = { Math::Vector3(x, -halfHeight, z), uv, this->color };
        //Vertex bottomVertex = { Math::Vector3(x, -halfHeight, z), Math::Vector3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT2((x / radius + 1) * 0.5f, (z / radius + 1) * 0.5f) };
        vertices.push_back(bottomVertex);
    }

    // Generate vertices for the side wall
    for (unsigned int i = 0; i < slices; ++i)
    {
        float theta = i * sliceStep;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        // Top vertex of the side
        Vertex3D sideTopVertex = { Math::Vector3(x, halfHeight, z), Math::Vector2(i / static_cast<float>(slices), 0.0f), this->color };
        //Vertex3D sideTopVertex = { Math::Vector3(x, halfHeight, z), Math::Vector3(x, 0.0f, z), DirectX::XMFLOAT2(i / static_cast<float>(slices), 0.0f) };
        vertices.push_back(sideTopVertex);

        // Bottom vertex of the side
        Vertex3D sideBottomVertex = { Math::Vector3(x, -halfHeight, z), Math::Vector2(i / static_cast<float>(slices), 1.0f), this->color };
        //Vertex3D sideBottomVertex = { Math::Vector3(x, -halfHeight, z), Math::Vector3(x, 0.0f, z), DirectX::XMFLOAT2(i / static_cast<float>(slices), 1.0f) };
        vertices.push_back(sideBottomVertex);
    }

	return vertices;
}