#pragma once

template<typename T>
struct Arg
{
	using Type = const T&;
	using Reference = T&;
};

template<>
struct Arg<unsigned char>
{
	using Type = unsigned char;
	using Reference = unsigned char&;
};

template<typename T >
struct Arg<T*>
{
	using Type = const T*;
	using Reference = T*;
};