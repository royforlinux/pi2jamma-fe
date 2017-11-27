#pragma once

#include "core/Arg.hpp"

template<typename T>
struct LifetimePolicyNone
{
    public:

        static void addRef(typename Arg<T>::Reference t) { }
        static void release(typename Arg<T>::Reference t) { }
};

template<typename T>
struct DeleteLifetimePolicy
{
public:
    static void addRef(typename Arg<T>::Reference t) {}
    static void release(typename Arg<T>::Reference t) { delete t; }
};
