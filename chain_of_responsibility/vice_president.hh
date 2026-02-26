#pragma once

#include "handler.hh"

class VicePresident : public Handler
{
public:
    void handle_request(int level) override;
};
