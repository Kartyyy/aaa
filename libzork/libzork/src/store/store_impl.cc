#include "store/store_impl.hh"

#include "exceptions.hh"

namespace libzork::store
{
	const story::Node* StoreImpl::get_active_node() const
    {
        return active_node_;
    }

    void StoreImpl::set_active_node(const story::Node* node)
    {
        active_node_ = node;
    }

    bool StoreImpl::has_variable(const std::string& name) const
    {
        return vars_.find(name) != vars_.end();
    }

    int StoreImpl::get_variable(const std::string& name) const
    {
        auto it = vars_.find(name);
        if (it == vars_.end())
            return 0;
        return it->second;
    }

    void StoreImpl::set_variable(const std::string& name, int value)
    {
        vars_[name] = value;
    }

    std::map<std::string, int> StoreImpl::get_inventory() const
    {
        std::map<std::string, int> inv;
        for (const auto& [k, v] : vars_)
        {
            const bool is_private = !k.empty() && k.back() == '_';
            if (!is_private && v > 0)
                inv.emplace(k, v);
        }
        return inv;
    }

} // namespace libzork::store
