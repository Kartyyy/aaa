#pragma once

#include "invalid_argument.hh"
#include "player.hh"

class Game
{
public:
    Game(int secret);
    void play(const Player& p1, const Player& p2) const;

private:
    int secret_;
};
