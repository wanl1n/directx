#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager() : ResourceManager() {}
TextureManager::~TextureManager() {}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* path)
{
    Texture* tex = nullptr; 

    try {
        tex = new Texture(path);
    } catch(...) {}

    return tex;
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* path)
{
    return std::static_pointer_cast<Texture>(createResourceFromFile(path));
}
