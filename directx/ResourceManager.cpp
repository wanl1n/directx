#include "ResourceManager.h"
#include <filesystem>

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t * path)
{
	WideString fullPath = std::filesystem::absolute(path);
	
	auto it = resourceMap.find(fullPath);
	if (it != resourceMap.end()) {
		return it->second;
	}

	Resource* raw = this->createResourceFromFileConcrete(path);

	if (raw) {
		ResourcePtr res(raw);
		resourceMap[path] = res;
		return res;
	}

	return nullptr;
}
