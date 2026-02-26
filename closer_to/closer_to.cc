#include "closer_to.hh"

CloserTo::CloserTo(int i)
  : i_{i}
{
}

bool CloserTo::operator()(int a, int b) const
{
    int da = (a >= i_) ? (a - i_) : (i_ - a);
    int db = (b >= i_) ? (b - i_) : (i_ - b);

    if (da != db)
        return da < db;
    return a < b;
}
