#pragma once

#include "core/StringSpan.hpp"

template<typename ContainerType = std::string>
ContainerType joinPath(const std::initializer_list<StringSpan>& parts)
{
	ContainerType s;
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