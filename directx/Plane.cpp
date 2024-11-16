#include "Plane.h"
#include "Vertex.h"
#include "PhysicsComponent.h"

Plane::Plane(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, PLANE, blending)
{
	this->color = WHITE;
	this->height = 50.0f;
	this->width = 50.0f;

	this->init();

	// Side Standing
	//this->setScale(Math::Vector3(50));
	this->setPosition(Math::Vector3(0, -2.0f, 0));
	this->setRotationX(1.57f);
	cc.world.setTranslation(transform.position);
	cc.world.setRotationX(transform.rotation.x);

	PhysicsComponent* rb = new PhysicsComponent(name + " Rigidbody", this);
	this->attachComponent(rb);
	rb->getRigidBody()->setType(BodyType::KINEMATIC);
	this->physOn = true;

	//this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Logo.jpg");
}

Plane::~Plane() {}

void Plane::initializeBuffers()
{
	// Set up the Index buffer.
	unsigned int indices[] = {
		//FRONT 0
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK 0
		4,5,6,
		6,7,4,
	};
	UINT size_indices = ARRAYSIZE(indices);
	this->ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indices, size_indices);
}

std::vector<Vertex3D> Plane::createVertices()
{
	std::vector<Vertex3D> vecVerts;
	int size = 8;

	Math::Vector3 xyzs[] = { // Cube Vertices
		// FRONT FACE
		Math::Vector3(-width, -height, 0),
		Math::Vector3(-width, height, 0),	
		Math::Vector3(width, height, 0),	
		Math::Vector3(width, -height, 0),	
		// BACK FACE
		Math::Vector3(width, -height, 0),	
		Math::Vector3(width, height, 0),	
		Math::Vector3(-width, height, 0),	
		Math::Vector3(-width, -height, 0)
	};

	Math::Vector2 uvs[] = {
		Math::Vector2(0, 1),
		Math::Vector2(0, 0),
		Math::Vector2(1, 0),
		Math::Vector2(1, 1)
	};

	Math::Vector4 multicolor[] = {
		PALEDOGWOOD,
		ROSYBROWN,
		PUCE,
		ROSETAUPE,
		WHITE,
		PINK,
		WHITE,
		PINK
	};

	//Set up the Vertex buffer.
	/*if (COLOR_SETTINGS == WHITE_COLORED) {

	}
	else if (COLOR_SETTINGS == RAINBOW_COLORED) {

	}*/

	for (int i = 0; i < size; i++) {
		Vertex3D vertex = { xyzs[i], uvs[i], multicolor[i]};
		vecVerts.push_back(vertex);
	}

	return vecVerts;
}

Math::Vector3 Plane::getScale()
{
	return Math::Vector3(50.0f, 50.0f, 1.0f);
}
