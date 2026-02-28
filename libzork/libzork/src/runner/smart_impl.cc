#include "runner/smart_impl.hh"

#include <libzork/exceptions.hh>

#include <yaml-cpp/yaml.h>

#include <cctype>
#include <string>

namespace libzork::runner
{
    static std::string lower(std::string s)
    {
        for (char& c : s)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return s;
    }

    static bool is_stop(const std::string& t)
    {
        if (t == "the" || t == "a" || t == "an" || t == "to" || t == "in"
            || t == "on" || t == "at" || t == "of" || t == "and" || t == "or")
            return true;

        if (t == "ca" || t == "ça" || t == "ne" || t == "pas" || t == "en"
            || t == "francais" || t == "français" || t == "marche")
            return true;

        return false;
    }

    SmartRunnerImpl::SmartRunnerImpl(std::unique_ptr<story::Story> story,
                                     const fs::path& synonyms_path,
                                     std::istream& is, std::ostream& os)
        : SmartRunner(std::move(story), is, os)
    {
        load_synonyms(synonyms_path);
    }

    void SmartRunnerImpl::load_synonyms(const fs::path& p)
    {
        try
        {
            const YAML::Node root = YAML::LoadFile(p.string());
            if (!root.IsMap())
                return;

            for (auto it = root.begin(); it != root.end(); ++it)
            {
                const std::string key = lower(it->first.as<std::string>());

                std::unordered_set<std::string> group;
                group.insert(key);

                const YAML::Node arr = it->second;
                if (arr && arr.IsSequence())
                    for (const auto& v : arr)
                        group.insert(lower(v.as<std::string>()));

                for (const auto& w : group)
                    syn_[w] = group;
            }
        }
        catch (const YAML::BadFile&)
        {
            // no synonym file
        }
    }

    std::unordered_set<std::string>
    SmartRunnerImpl::tokenize(const std::string& str) const
    {
        std::unordered_set<std::string> out;
        std::string cur;

        auto flush = [&]()
        {
            if (cur.empty())
                return;

            const std::string tok = lower(cur);

            if (tok.size() < 3 || is_stop(tok))
            {
                cur.clear();
                return;
            }

            out.insert(tok);
            cur.clear();
        };

        for (unsigned char ch : str)
        {
            if (std::isalnum(ch))
                cur.push_back(static_cast<char>(ch));
            else
                flush();
        }
        flush();
        return out;
    }

    bool SmartRunnerImpl::matches_token(
        const std::unordered_set<std::string>& user_tokens,
        const std::string& choice_token) const
    {
        if (user_tokens.contains(choice_token))
            return true;

        if (auto it = syn_.find(choice_token); it != syn_.end())
        {
            for (const auto& s : it->second)
                if (user_tokens.contains(s))
                    return true;
        }
        return false;
    }

    bool SmartRunnerImpl::has_unmatched_token(
        const std::unordered_set<std::string>& user_tokens,
        const std::unordered_set<std::string>& choice_tokens) const
    {
        for (const auto& t : choice_tokens)
        {
            if (t.size() < 3 || is_stop(t))
                continue;

            if (!matches_token(user_tokens, t))
                return true;
        }
        return false;
    }

    void SmartRunnerImpl::process_input()
    {
        const story::Node* cur = story_->get_current();
        if (!cur)
            throw RunnerQuit();

        const auto labels = cur->list_choices(true);
        if (labels.empty())
            throw RunnerQuit();

        std::string line;
        if (!std::getline(is_, line))
            throw RunnerQuit();

        const auto user = tokenize(line);
        if (user.empty())
            throw RunnerInterrupt("I beg your pardon?");

        std::size_t best = labels.size();
        std::size_t best_score = 0;

        for (std::size_t i = 0; i < labels.size(); ++i)
        {
            const auto choice = tokenize(labels[i]);
            if (choice.empty())
                continue;

            if (has_unmatched_token(user, choice))
                continue;

            const std::size_t score = choice.size();
            if (best == labels.size() || score > best_score)
            {
                best = i;
                best_score = score;
            }
        }

        if (best == labels.size())
            throw RunnerInterrupt("I beg your pardon?");

        const story::Node* next = cur->get_choice(best, true);
        if (!next)
            throw RunnerInterrupt("I beg your pardon?");

        story_->set_current(next);
    }

} // namespace libzork::runner
