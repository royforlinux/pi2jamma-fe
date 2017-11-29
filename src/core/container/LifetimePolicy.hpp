#pragma once

#include "core/Arg.hpp"

template<typename T>
struct LifetimePolicyNone
{
    public:

        static void addRef(const T& t) { }
        static void release(const T& t) { }
};

template<typename T>
struct DeleteLifetimePolicy
{
public:
    static void addRef(T& t) {}
    static void release(T& t) { delete t; }
};
