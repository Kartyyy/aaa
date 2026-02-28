#ifndef NODE_IMPL_HH
#define NODE_IMPL_HH

#include <libzork/story/node.hh>
#include <filesystem>
#include <string>
#include <vector>

#include "story/choice.hh"
namespace libzork::story
{

    class NodeImpl : public Node
    {
    public:
	            NodeImpl(const std::string& name, const std::filesystem::path& script_path);
        ~NodeImpl() override = default;

        const std::string& get_name() const override;
        const std::string& get_text() const override;

        const Node* get_choice(std::size_t index,
                               bool check_conditions = true) const override;
        std::vector<std::string>
        list_choices(bool check_conditions = true) const override;
        void add_choice(
            const Node* other, const std::string& text,
            std::vector<std::unique_ptr<vars::Condition>> conditions = {},
            std::vector<std::unique_ptr<vars::Action>> actions = {}) override;
	 private:
        std::string name_;
        std::string text_;
        std::vector<Choice> choices_;
    };

    const NodeImpl& to_impl(const Node& node);
    NodeImpl& to_impl(Node& node);

} // namespace libzork::story
#endif // !NODE_IMPL_HH
