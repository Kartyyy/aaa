#ifndef STORY_IMPL_HH
#define STORY_IMPL_HH

#include <libzork/story/story.hh>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


namespace libzork::story
{

    class StoryImpl : public Story
    {
    public:
    	StoryImpl(std::string title,
                  std::unique_ptr<store::Store> store,
                  std::vector<std::unique_ptr<Node>> nodes,
                  const Node* current);

        ~StoryImpl() override = default;

        const std::string& get_title() const override;
        const Node* get_current() const override;
        void set_current(const Node* node) override;
        const store::Store* get_store() const override;
        std::ostream& display(std::ostream& os) const override;

        const Node* find_node(const std::string& name) const; // find with yaml

    private:
        std::string title_;
        std::unique_ptr<store::Store> store_;
        std::vector<std::unique_ptr<Node>> nodes_; 
        std::unordered_map<std::string, const Node*> by_name_;
        const Node* current_;
    };

    const StoryImpl& to_impl(const Story& story);
    StoryImpl& to_impl(Story& story);

} // namespace libzork::story
#endif // !STORY_IMPL_HH
