#pragma once

#include "core/StringSpan.hpp"
#include <vector>
#include <string>

#define PATH_SEP_STR "/"
const char PATH_SEP_CHAR = '/';

std::string joinPath(const std::initializer_list<StringSpan>& parts);
std::vector<std::string> splitPath(StringSpan stringSpan);
std::string getPathEntryName(StringSpan stringSpan);

