#ifndef STORY_CHOICE_HH
#define STORY_CHOICE_HH

#include <libzork/vars/action.hh>
#include <libzork/vars/condition.hh>

#include <memory>
#include <string>
#include <vector>

namespace libzork::story
{
    class Node;

    class Choice
    {
    public:
        Choice(const Node* target, std::string text,
               std::vector<std::unique_ptr<vars::Condition>> conditions = {},
               std::vector<std::unique_ptr<vars::Action>> actions = {})
            : target_(target)
            , text_(std::move(text))
            , conditions_(std::move(conditions))
            , actions_(std::move(actions))
        {}

        const Node* target() const { return target_; }
        const std::string& text() const { return text_; }

        bool available() const
        {
            for (const auto& c : conditions_)
                if (c && !c->apply())
                    return false;
            return true;
        }

        void execute() const
        {
            for (const auto& a : actions_)
                if (a)
                    a->apply();
        }

    private:
        const Node* target_;
        std::string text_;
        std::vector<std::unique_ptr<vars::Condition>> conditions_;
        std::vector<std::unique_ptr<vars::Action>> actions_;
    };
} // namespace libzork::story

#endif // STORY_CHOICE_HH
