#ifndef ACTION_IMPL_HH
#define ACTION_IMPL_HH

#include <libzork/vars/action.hh>

#include <string>

namespace libzork::vars
{
    class ActionImpl : public Action
    {
    public:
        ActionImpl(store::Store& store, std::string variable, std::string action,
                   int value);

        void apply() const override;

    private:
        store::Store* store_;
        std::string variable_;
        std::string action_;
        int value_;
    };
} // namespace libzork::vars

#endif // !ACTION_IMPL_HH
