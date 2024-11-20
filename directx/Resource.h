#pragma once
#include <string>
class Resource
{
	protected:
		std::wstring path;

	public:
		Resource(const wchar_t* path);
		virtual ~Resource();
};

