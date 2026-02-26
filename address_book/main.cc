#include <iostream>
#include <string>
#include <vector>

#include "address_book.hh"

int main()
{
    auto b = AddressBook{};

    std::cout << "Adding multiple contacts to the address book.\n";

    b.add("Cyril Berger", "cyril.berger@epita.fr", "33612983402");
    b.add("Thibault Allancon", "thibault.allancon@epita.fr", "33612983409");
    b.add("Cyril Berger", "cyril.berger@epita.fr", "33628359602");
    b.add("Hugo Wahl", "hugo.wahl@epita.fr", "3398560923");
    b.add("Dominique Michel", "dominique.michel@epita.fr", "3345096792");

    std::cout << "Searching for Maya El Gemayel:\n";
    auto v = b.find("Maya El Gemayel");
    for (auto it = v.begin(); it != v.end(); it++)
        std::cout << *it;

    std::cout << "Searching for Thibault Allancon:\n";
    v = b.find("Thibault Allancon");
    for (auto it = v.begin(); it != v.end(); it++)
        std::cout << *it;

    std::cout << "Searching for Cyril Berger:\n";
    v = b.find("Cyril Berger");
    for (auto it = v.begin(); it != v.end(); it++)
        std::cout << *it;

    std::cout << b;

    std::cout << "Erasing the second Cyril Berger.\n";
    b.remove("Cyril Berger", 1);

    std::cout << b;

    return 0;
}
