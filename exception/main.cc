#include <iostream>

#include "game.hh"
#include "invalid_argument.hh"
#include "player.hh"

int main()
{
    auto g = Game{ 42 };
    std::string n1 = "Toto";
    std::string n2 = "Frodo";
    std::string n3 = "Feanor";
    std::string n4 = "Pikachu";
    std::string n5 = "Baby";
    std::string n6 = "";

    // Should not throw!!
    Player p1 = Player{ n1, 9, 3 };
    Player p2 = Player{ n2, 51, 5 };
    Player p3 = Player{ n4, 25, 5000 };

    try
    {
        Player p4 = Player{ n3, 3142, 42 };
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        Player p5 = Player{ n5, -1, 1 };
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        Player p6 = Player{ n6, 19, 1 };
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        Player p7 = Player{ n1, 9, 3 };
        g.play(p7, p7);
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }

    Player p8 = Player{ n1, 9, 3 };
    Player p9 = Player{ n2, 51, -18 };
    g.play(p8, p9);
}
