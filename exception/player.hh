#pragma once

#include <iostream>

#include "invalid_argument.hh"

class Player
{
public:
    Player(const std::string& name, int age, int guess);

    int get_guess() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& b);

    bool operator==(const Player& p) const;
    bool operator!=(const Player& p) const;

private:
    std::string name_;
    int age_;

    int guess_;
};

std::ostream& operator<<(std::ostream& os, const Player& p);
