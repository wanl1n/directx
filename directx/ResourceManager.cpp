#include "ResourceManager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t * path)
{
#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
	 WideString fullPath = std::experimental::filesystem::absolute(path);
#endif

#if _MSC_VER >= 1920 && __cplusplus > 201402L 
	 WideString fullPath = std::filesystem::absolute(path);
#endif

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
