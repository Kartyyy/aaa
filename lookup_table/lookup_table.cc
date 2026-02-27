#include "lookup_table.hh"

std::optional<long> LookupTable::get(int x)
{
    auto it = table_.find(x);
    if (it == table_.end())
        return std::nullopt;
    return it->second;
}

void LookupTable::set(int x, long value)
{
    table_[x] = value;
}
