#ifndef SMART_IMPL_HH
#define SMART_IMPL_HH

#include <libzork/runner/smart.hh>

#include <unordered_map>
#include <unordered_set>

namespace libzork::runner
{
    class SmartRunnerImpl : public SmartRunner
    {
    public:
        SmartRunnerImpl(std::unique_ptr<story::Story> story,
                        const fs::path& synonyms_path,
                        std::istream& is, std::ostream& os);

        void process_input() override;

        std::unordered_set<std::string>
        tokenize(const std::string& str) const override;

        bool has_unmatched_token(
            const std::unordered_set<std::string>& user_tokens,
            const std::unordered_set<std::string>& choice_tokens) const override;

    private:
        void load_synonyms(const fs::path& p);

        bool matches_token(const std::unordered_set<std::string>& user_tokens,
                           const std::string& choice_token) const;

        std::unordered_map<std::string, std::unordered_set<std::string>> syn_;
    };

} // namespace libzork::runner

#endif // !SMART_IMPL_HH
