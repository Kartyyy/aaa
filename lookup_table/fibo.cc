#include "fibo.hh"

long Fibo::operator()(int x)
{
    if (x <= 1)
        return x;

    std::optional<long> opt_lookup_table = lookup_table_.get(x);
    if (opt_lookup_table)
        return *opt_lookup_table;

    auto res = (*this)(x - 1) + (*this)(x - 2);
    lookup_table_.set(x, res);
    return res;
}
