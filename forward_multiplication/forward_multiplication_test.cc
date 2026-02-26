#include <iostream>
#include <string>

#include "forward_multiplication.hh"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " 'number' 'number'" << std::endl;
        return 1;
    }

    auto lhs = std::stoi(argv[1]);
    auto rhs = std::stoi(argv[2]);

    auto mult_by_lhs = mult_by(lhs);

    std::cout << mult_by(lhs)(rhs) << '\n';
    std::cout << mult_by_lhs(rhs) << std::endl;
}
