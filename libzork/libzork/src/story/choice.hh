#ifndef CHOICE_HH
#define CHOICE_HH

#include <string>

namespace libzork::story
{

    class Node;

    class Choice
    {
    public:
        Choice(const Node* target, std::string text)
            : target_(target)
            , text_(std::move(text))
        {}

        const Node* target() const { return target_; }
        const std::string& text() const { return text_; }

    private:
        const Node* target_;
        std::string text_;
    };

} // namespace libzork::story
#endif // !CHOICE_HH
