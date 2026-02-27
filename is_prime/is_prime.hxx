#pragma once

constexpr bool is_prime(unsigned n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if ((n % 2) == 0u)
        return false;

    for (unsigned i = 3; (static_cast<unsigned long long>(i) * i) <= n; i += 2)
    {
        if ((n % i) == 0)
            return false;
    }
    return true;
}
