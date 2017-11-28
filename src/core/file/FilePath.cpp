#include "core/file/FilePath.hpp"


std::string joinPath(const std::initializer_list<StringSpan>& parts)
{
	std::string s;
	bool first = true;
	for(auto&& part: parts)
	{
		if(!first) {
			s += "/";
		}
		else
		{
			first = false;
		}

		s.insert(s.end(), part.begin(), part.end());
	}

	return s;
}