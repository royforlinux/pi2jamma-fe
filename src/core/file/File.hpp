#pragma once

#include "core/Result.hpp"
#include <stdio.h>

using FileSize = uint64_t;

class File
{
public:

	static Result load(std::string& s, const char* pFilePath);

	enum class OpenMode { Read, Write };

	File();
	~File();

	Result open(const char* pFilePath, OpenMode openMOde);
	Result readExactly(void* pBuf, FileSize bytes);
	Result getSize(FileSize& size);

	void close();

private:

	FILE* mpFile;
};
