#pragma once

#include <optional>
#include <unordered_map>

class LookupTable
{
public:
    std::optional<long> get(int x);
    void set(int x, long value);

private:
    std::unordered_map<int, long> table_;
};
