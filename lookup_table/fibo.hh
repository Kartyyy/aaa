#pragma once

#include "lookup_table.hh"

class Fibo
{
private:
    LookupTable lookup_table_;

public:
    long operator()(int x);
};
