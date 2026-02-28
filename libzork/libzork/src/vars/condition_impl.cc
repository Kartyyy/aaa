#include "vars/condition_impl.hh"

#include <stdexcept>
#include <utility>

namespace libzork::vars
{
    ConditionImpl::ConditionImpl(const store::Store& store, std::string variable,
                                 std::string comparison, int value)
        : store_(&store)
        , variable_(std::move(variable))
        , comparison_(std::move(comparison))
        , value_(value)
    {}

    bool ConditionImpl::apply() const
    {
        const int lhs = store_->get_variable(variable_);
        const int rhs = value_;
        const std::string& op = comparison_;

        if (op == "==" || op == "=")
            return lhs == rhs;
        if (op == "!=")
            return lhs != rhs;
        if (op == "<")
            return lhs < rhs;
        if (op == "<=")
            return lhs <= rhs;
        if (op == ">")
            return lhs > rhs;
        if (op == ">=")
            return lhs >= rhs;

        throw std::invalid_argument("invalid comparison: " + op);
    }
} // namespace libzork::vars
