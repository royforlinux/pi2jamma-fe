#pragma once

#include "core/String.hpp"

class LoadTextContext
{
public:
	CStrArg getData() { return mData; }
private:
	CStr mData;
};