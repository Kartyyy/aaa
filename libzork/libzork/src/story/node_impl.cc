#include "story/node_impl.hh"

#include <fstream>
#include <sstream>
#include <utility>
#include <stdexcept>
#include <iostream>

#include "exceptions.hh"

namespace libzork::story
{
	static std::string read_file(const std::filesystem::path& p)
{
    std::ifstream ifs(p);
    if (!ifs.is_open())
        throw std::runtime_error("cannot open script: " + p.string());

    std::ostringstream oss;
    oss << ifs.rdbuf();
    return oss.str();
}

	libzork::story::NodeImpl::NodeImpl(const std::string& name,
                                   const std::filesystem::path& script_path)
    : name_(name)
    , text_(read_file(script_path))
{
std::cerr << "[DEBUG] loading " << script_path << "\n";
}

    const std::string& NodeImpl::get_name() const
    {
      return name_;
    }

    const std::string& NodeImpl::get_text() const
    {
        return text_;
    }

    const Node* NodeImpl::get_choice(size_t index, bool check_conditions) const
    {
        (void)check_conditions;
        if (index >= choices_.size())
            return nullptr;
        return choices_[index].target();
    }

    std::vector<std::string> NodeImpl::list_choices(bool check_conditions) const
    {
        (void)check_conditions;
        std::vector<std::string> res;
        res.reserve(choices_.size());
        for (const auto& c : choices_)
            res.push_back(c.text());
        return res;
    }

    void NodeImpl::add_choice(
        const Node* other, const std::string& text,
        std::vector<std::unique_ptr<vars::Condition>> conditions,
        std::vector<std::unique_ptr<vars::Action>> actions)
    {
        (void)conditions;
        (void)actions;
	choices_.emplace_back(other, text);
    }

    const NodeImpl& to_impl(const Node& node)
    {
	    return static_cast<const NodeImpl&>(node);
    }

    NodeImpl& to_impl(Node& node)
    {
       return static_cast<NodeImpl&>(node);
    }

} // namespace libzork::story
