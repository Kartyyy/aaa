#include "story/story_impl.hh"

#include <utility>

namespace libzork::story
{
    StoryImpl::StoryImpl(std::string title,
                         std::unique_ptr<store::Store> store,
                         std::vector<std::unique_ptr<Node>> nodes,
                         const Node* current)
        : title_(std::move(title))
        , store_(std::move(store))
        , nodes_(std::move(nodes))
        , by_name_()
        , current_(current)
    {
        by_name_.reserve(nodes_.size());
        for (const auto& up : nodes_)
            by_name_.emplace(up->get_name(), up.get());

        if (store_)
            store_->set_active_node(current_);
    }

    const std::string& StoryImpl::get_title() const
    {
        return title_;
    }

    const Node* StoryImpl::get_current() const
    {
        return current_;
    }

    void StoryImpl::set_current(const Node* node)
    {
        current_ = node;
        if (store_)
            store_->set_active_node(node);
    }

    const store::Store* StoryImpl::get_store() const
    {
        return store_.get();
    }

    const Node* StoryImpl::find_node(const std::string& name) const
    {
        auto it = by_name_.find(name);
        if (it == by_name_.end())
            return nullptr;
        return it->second;
    }


    std::ostream& StoryImpl::display(std::ostream& os) const
{
    (void)os;
    return os;
}

    const StoryImpl& to_impl(const Story& story)
    {
        return static_cast<const StoryImpl&>(story);
    }

    StoryImpl& to_impl(Story& story)
    {
        return static_cast<StoryImpl&>(story);
    }

} // namespace libzork::story
