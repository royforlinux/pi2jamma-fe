#pragma once

#include "core/result.hpp"
#include <stdio.h>

class File
{
public:

	static Result load(std::string& s, const char* pFilePath);

	enum class OpenMode { Read, Write };

	File();
	~File();

	Result open(const char* pFilePath, OpenMode openMOde);
	Result readExactly(void* pBuf, size_t bytes);
	Result getSize(size_t& size);

	void close();

private:

	FILE* mpFile;
};