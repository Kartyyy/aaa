#pragma once

#include "handler.hh"

class President : public Handler
{
public:
    void handle_request(int level) override;
};
