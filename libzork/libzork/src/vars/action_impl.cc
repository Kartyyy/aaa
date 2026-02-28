#include "vars/action_impl.hh"

#include <stdexcept>
#include <utility>

namespace libzork::vars
{
    ActionImpl::ActionImpl(store::Store& store, std::string variable,
                           std::string action, int value)
        : store_(&store)
        , variable_(std::move(variable))
        , action_(std::move(action))
        , value_(value)
    {}

    void ActionImpl::apply() const
    {
        const std::string& op = action_;

        if (op == "=" || op == ":=" || op == "set")
        {
            store_->set_variable(variable_, value_);
            return;
        }

        if (op == "+=" || op == "add" || op == "inc")
        {
            const int cur = store_->get_variable(variable_);
            store_->set_variable(variable_, cur + value_);
            return;
        }

        if (op == "-=" || op == "sub" || op == "dec")
        {
            const int cur = store_->get_variable(variable_);
            store_->set_variable(variable_, cur - value_);
            return;
        }

        // Unknown action => strict
        throw std::invalid_argument("invalid action: " + op);
    }
} // namespace libzork::vars
