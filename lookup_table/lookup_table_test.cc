#include <iostream>

#include "fibo.hh"

int main()
{
    auto fibo = Fibo{};
    std::cout << fibo(42) << '\n';
}
