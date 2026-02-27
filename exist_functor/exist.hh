#pragma once

#include <set>
template <class T>
class Exist
{
public:
        bool operator()(const T& value);

private:
        std::set<T> seen_;
};

#include "exist.hxx"
