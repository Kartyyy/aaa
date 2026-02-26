#pragma once

struct CloserTo
{
    CloserTo(int i);

    bool operator()(int a, int b) const;

private:
    int i_;
};
