#include "player.hh"

Player::Player(const std::string& name, int age, int guess)
    : name_(name)
    , age_(age)
    , guess_(guess)
{
     if (name.empty())
        throw InvalidArgumentException("Name can't be empty.");

    if (age < 0)
        throw InvalidArgumentException("Well, it seems you are not born yet.");

    if (age > 150)
        throw InvalidArgumentException("Sorry gramp, too old to play.");
}

int Player::get_guess() const
{
    return guess_;
}

bool Player::operator==(const Player& p) const
{
    return this == &p;
}

bool Player::operator!=(const Player& p) const
{
    return this != &p;
}

std::ostream& operator<<(std::ostream& os, const Player& p)
{
    return os << p.name_ << '(' << p.age_ << ')';
}
