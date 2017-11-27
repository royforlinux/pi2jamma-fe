#include "core/file/File.hpp"

#include <sstream>

File::File()
	: mpFile(nullptr)
{
}


File::~File()
{
	close();
}

Result File::open(const char* pFilePath, OpenMode openMode) {
	close();

	const char* pMode =
		(OpenMode::Read == openMode)
			? "rb"
			: "wb";

	mpFile =
		fopen(
			pFilePath,
			pMode);


	if(nullptr == mpFile) {
		std::stringstream ss;
		ss << "Failed to open file:'" << pFilePath <<"', Mode:'" << pMode << "'.";

		return Result::makeFailureWithString(ss.str());

	}

	return Result::makeSuccess();

}

Result File::readExactly(void* pBuf, FileSize bytes)
{
	auto result = fread(pBuf, 1, bytes, mpFile);
	if(result != bytes) {
		std::stringstream ss;
		ss
			<< "Failed to read exactly: "
			<< bytes
			<< " got: "
			<< result;

		return Result::makeFailureWithString(ss.str());
	}

	return Result::makeSuccess();
}

Result File::getSize(FileSize& size)
{
	auto originalPositionOrError = ftell(mpFile);
	
	if(-1L == originalPositionOrError) {
		return Result::makeFailureWithStringLiteral("ftell() failed");
	}

	if( 0 != fseek(mpFile, 0, SEEK_END)) {
		return Result::makeFailureWithStringLiteral("fseek() failed.");
	}

	auto endPositionOrError = ftell(mpFile);

	if(-1L == endPositionOrError) {
		return Result::makeFailureWithStringLiteral("ftell() failed");
	}	

	if(0 !=fseek(mpFile, 0, originalPositionOrError)) {
		return Result::makeFailureWithStringLiteral("fseek() failed.");
	}

	size = endPositionOrError;

	return Result::makeSuccess();
}

void File::close()
{
	if(nullptr != mpFile) {
		fclose(mpFile);
	}
}


 Result File::load(std::string& s, const char* pFilePath) {

	File file;

	Result r = file.open(pFilePath, File::OpenMode::Read);
	if(r.peekFailed()) {
		return r;
	}

	size_t fileSize = 0;
	r = file.getSize(fileSize);
	if(r.peekFailed()) {
		return r;
	}

	std::string tempString;
	tempString.reserve(fileSize + 1);

	r = file.readExactly(&tempString[0], fileSize);
	if(r.peekFailed()) {
		return r;
	}

	tempString[fileSize] = '0';

	s = std::move(tempString);

	return Result::makeSuccess();
}