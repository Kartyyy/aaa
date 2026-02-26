#include "director.hh"
#include "president.hh"
#include "vice_president.hh"

int main()
{
    auto p = President{};
    auto vp = VicePresident{};
    vp.set_successor(&p);
    auto d = Director{};
    d.set_successor(&vp);

    d.handle_request(1);
    d.handle_request(10);
    d.handle_request(2);
    d.handle_request(5);
    d.handle_request(4);
    d.handle_request(2);
    d.handle_request(9);

    return 0;
}
