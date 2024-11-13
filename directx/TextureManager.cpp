#include "TextureManager.h"
#include "Texture.h"
#include "stb_image.h"

#include "GraphicsEngine.h"

TextureManager::TextureManager() : ResourceManager()
{
    /*int txtWidth = 0;
    int txtHeight = 0;
    ID3D11ShaderResourceView* texture = NULL;
    bool ret = LoadTextureFromFile("Textures/Logo.jpg", &texture, &txtWidth, &txtHeight);
    IM_ASSERT(ret);

    if (ret)
    {
        TextureNames txtNames;
        TextureData txt = { texture, txtWidth, txtHeight };
        this->txtTable[txtNames.LOGO] = txt;
    }*/
}

TextureManager::~TextureManager() {}

//// Simple helper function to load an image into a DX11 texture with common settings
//bool TextureManager::LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
//{
//    // Load from disk into a raw RGBA buffer
//    int image_width = 0;
//    int image_height = 0;
//    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
//    if (image_data == NULL)
//        return false;
//
//    // Create texture
//    D3D11_TEXTURE2D_DESC desc;
//    ZeroMemory(&desc, sizeof(desc));
//    desc.Width = image_width;
//    desc.Height = image_height;
//    desc.MipLevels = 1;
//    desc.ArraySize = 1;
//    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    desc.SampleDesc.Count = 1;
//    desc.Usage = D3D11_USAGE_DEFAULT;
//    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//    desc.CPUAccessFlags = 0;
//
//    ID3D11Texture2D* pTexture = NULL;
//    D3D11_SUBRESOURCE_DATA subResource;
//    subResource.pSysMem = image_data;
//    subResource.SysMemPitch = desc.Width * 4;
//    subResource.SysMemSlicePitch = 0;
//    GraphicsEngine::get()->getRenderSystem()->getDevice()->CreateTexture2D(&desc, &subResource, &pTexture);
//
//    // Create texture view
//    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//    ZeroMemory(&srvDesc, sizeof(srvDesc));
//    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//    srvDesc.Texture2D.MipLevels = desc.MipLevels;
//    srvDesc.Texture2D.MostDetailedMip = 0;
//    GraphicsEngine::get()->getRenderSystem()->getDevice()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
//    pTexture->Release();
//
//    *out_width = image_width;
//    *out_height = image_height;
//    stbi_image_free(image_data);
//
//    return true;
//}
//
//// Open and read a file, then forward to LoadTextureFromMemory()
//bool TextureManager::LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
//{
//    FILE* f;
//    fopen_s(&f, file_name, "rb");
//
//    if (f == NULL) return false;
//
//    fseek(f, 0, SEEK_END);
//    size_t file_size = (size_t)ftell(f);
//    if (file_size == -1) return false;
//
//    fseek(f, 0, SEEK_SET);
//    void* file_data = IM_ALLOC(file_size);
//
//    fread(file_data, 1, file_size, f);
//    bool ret = LoadTextureFromMemory(file_data, file_size, out_srv, out_width, out_height);
//    IM_FREE(file_data);
//    return ret;
//}

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
