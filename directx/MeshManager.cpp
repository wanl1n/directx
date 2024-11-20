#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager() : ResourceManager() {}
MeshManager::~MeshManager() {}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* path)
{
    Mesh* mesh = nullptr;

    try {
        mesh = new Mesh(path);
    }
    catch (...) {}

    return mesh;
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* path)
{
    return std::static_pointer_cast<Mesh>(createResourceFromFile(path));
}
