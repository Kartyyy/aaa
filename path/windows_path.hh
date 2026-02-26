#pragma once

#include "path.hh"

class WindowsPath : public Path
{
public:
    std::string to_string() const override;
};
