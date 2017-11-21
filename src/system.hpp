#pragma once

#include "result.hpp"

class System
{
	public:

	 	static Result exec(const char* cmd, std::string& output);
};