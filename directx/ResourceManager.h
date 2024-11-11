#pragma once
#include <unordered_map>
#include <string>

#include "Prerequisites.h"
#include "Resource.h"

class ResourceManager
{
	public:
		typedef std::wstring WideString;

	private:
		std::unordered_map<WideString, ResourcePtr> resourceMap;

	public:
		ResourceManager();
		virtual ~ResourceManager();

		ResourcePtr createResourceFromFile(const wchar_t* path);

	protected:
		virtual Resource* createResourceFromFileConcrete(const wchar_t * path) = 0;
};

