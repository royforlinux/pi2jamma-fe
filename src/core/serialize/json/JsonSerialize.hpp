#pragma once

#include "core/file/FileUtil.hpp"
#include "core/parse/Parser.hpp"
#include "core/parse/StringDecoder.hpp"
#include "core/serialize/json/JsonReadStream.hpp"

template<typename T>
Result loadJson(T& t, CStr fileName)
{
	std::vector<char> fileData;
	Result r = readFile(fileName, fileData);
	if(r.peekFailed()){
		return r;
	}

	const char* pData = fileData.data();

	StringDecoder dataStream(pData, pData + fileData.size());
	std::vector<char> workArea;
	
	OmParser<StringDecoder> parser(
		dataStream,
		workArea,
		fileName);

	JsonReadStream<OmParser<StringDecoder>> jsonReadStream(parser);

	return load(t, jsonReadStream);
};