#pragma once
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
	public:
		MeshManager();
		~MeshManager();

	protected:
		virtual Resource* createResourceFromFileConcrete(const wchar_t* path);

	public:
		MeshPtr createMeshFromFile(const wchar_t* path);
};

