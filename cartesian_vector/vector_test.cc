#include <cmath>
#include <iostream>

#include "vector.hh"

double pi()
{
    return std::atan2(0., -1.);
}

int main()
{
    std::cout << "default state pi (double) : " << pi() << '\n';
    auto piVector = Vector{ pi(), pi() };
    auto t = Vector(-1.0E-7, 6.812031E-4);
    std::cout << "piVector :\n" << piVector << '\n';
    std::cout << "t + piVector :\n" << t + piVector << '\n';

    auto u = Vector{ 1923, 8 };
    std::cout << "u :\n" << u << '\n';
    std::cout << "default state (double) : " << u * t << '\n';
    t -= u;
    std::cout << "t :\n" << t << '\n';
    std::cout << "t * 3 :\n" << t * 3 << '\n';

    return 0;
}
