#include <libzork/story/story.hh>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <yaml-cpp/yaml.h>

#include <libzork/store/store.hh>
#include <libzork/story/node.hh>

#include "story/story_impl.hh"

namespace libzork::story
{
    static fs::path resolve_scripts_dir(const fs::path& yml_path, const YAML::Node& root)
    {
        fs::path p = root["scripts-path"].as<std::string>();
        if (p.is_relative())
            p = yml_path.parent_path() / p;
        return p;
    }

    std::unique_ptr<Story> make_story(const fs::path& path)
    {
        const YAML::Node root = YAML::LoadFile(path.string());
        const YAML::Node story = root["story"];

        const std::string title = root["title"].as<std::string>();
        const fs::path scripts_dir = resolve_scripts_dir(path, root);

        std::vector<std::unique_ptr<Node>> nodes;
        nodes.reserve(story.size());

        std::unordered_map<std::string, Node*> by_name;
        by_name.reserve(story.size());

        // create
        for (const auto& n : story)
        {
            const std::string name = n["name"].as<std::string>();
            const fs::path script = scripts_dir / n["script"].as<std::string>();

            auto node = make_node(name, script);
            by_name[name] = node.get();
            nodes.emplace_back(std::move(node));
        }

        // connect
        for (const auto& n : story)
        {
            Node* from = by_name[n["name"].as<std::string>()];
            for (const auto& c : n["choices"])
                from->add_choice(by_name[c["target"].as<std::string>()],
                                 c["text"].as<std::string>());
        }

        auto st = libzork::store::make_store();
        const Node* current = nodes.empty() ? nullptr : nodes.front().get();
        return std::make_unique<StoryImpl>(title, std::move(st), std::move(nodes), current);
    }

} // namespace libzork::story
