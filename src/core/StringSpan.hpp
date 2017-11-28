#pragma once

#include "core/debug.hpp"

#include <stddef.h>
#include <string>
#include <memory.h>

class StringSpan
{
public:
	StringSpan(const char* pCStr);
	StringSpan(const char* pBegin, const char* pEnd);
	StringSpan(const char* pBegin, size_t length);
	StringSpan(const std::string& str);
	StringSpan(const std::string& str, size_t offset, size_t length);

	size_t size() const;

	const char& operator[](size_t i) const;

	const char* begin() const;
	const char* end() const;

private:

	const char* mpBegin;
	const char* mpEnd;
};

inline StringSpan::StringSpan(const char* pCString)
	: mpBegin(pCString)
	, mpEnd(pCString + strlen(pCString))
{
}

inline StringSpan::StringSpan(const char* pBegin, const char* pEnd)
	: mpBegin(pBegin)
	, mpEnd(pEnd)
{}

inline StringSpan::StringSpan(const char* pBegin, size_t length)
	: mpBegin(pBegin)
	, mpEnd(pBegin + length)
{}

inline StringSpan::StringSpan(const std::string& str)
	: mpBegin(str.c_str())
	, mpEnd(mpBegin + str.size())
{}

inline size_t StringSpan::size() const
{
	return mpEnd - mpBegin;
}

inline StringSpan::StringSpan(
	const std::string& str,
	size_t offset,
	size_t length)
	: mpBegin(str.c_str() + offset)
	, mpEnd(str.c_str() + offset + length)
{
	ASSERT((offset + length) <= str.size());
}

inline const char& StringSpan::operator[](size_t i) const
{
	ASSERT(i < size());
	return mpBegin[i];
}

inline const char* StringSpan::begin() const
{
	return mpBegin;
}

inline const char* StringSpan::end() const
{
	return mpEnd;
}





