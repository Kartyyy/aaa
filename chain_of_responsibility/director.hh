#pragma once

#include "handler.hh"

class Director : public Handler
{
public:
    void handle_request(int level) override;
};
