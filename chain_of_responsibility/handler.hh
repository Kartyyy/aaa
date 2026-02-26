#pragma once

class Handler
{
public:
    Handler(Handler* next = nullptr);
    void set_successor(Handler* h);
    virtual void handle_request(int level) = 0;

protected:
    void forward_request(int level);

private:
    Handler* next_;
};
