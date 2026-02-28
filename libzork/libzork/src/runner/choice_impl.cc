#include "runner/choice_impl.hh"

#include <libzork/exceptions.hh>
#include <sstream>
#include <string>
#include <cctype>

#include "exceptions.hh"

namespace libzork::runner
{
    static bool only_spaces(const std::string& s)
    {
        for (unsigned char c : s)
            if (!std::isspace(c))
                return false;
        return true;
    }

    void ChoiceRunnerImpl::print_script() const
    {
        const story::Node* cur = story_->get_current();
        if (!cur)
            return;

        os_ << cur->get_text();
        if (!cur->get_text().empty() && cur->get_text().back() != '\n')
            os_ << '\n';

        const auto labels = cur->list_choices(true);
        if (!labels.empty())
        {
            os_ << '\n';
            for (std::size_t i = 0; i < labels.size(); ++i)
                os_ << (i + 1) << ". " << labels[i] << '\n';
            os_ << '\n';
        }

        os_ << std::flush;
    }

    void ChoiceRunnerImpl::process_input()
    {
        const story::Node* cur = story_->get_current();
        if (!cur)
            throw RunnerQuit();

        const auto labels = cur->list_choices(true);
        if (labels.empty())
            throw RunnerQuit();

        const std::string msg =
            "Please input an integer between 1 and " + std::to_string(labels.size());

        std::size_t n = 0;
        if (!(is_ >> n))
        {
            is_.clear();
            std::string junk;
            std::getline(is_, junk);
            throw RunnerInterrupt(msg);
        }

        std::string rest;
        std::getline(is_, rest); 

        if (!only_spaces(rest))
            throw RunnerInterrupt(msg);

        if (n < 1 || n > labels.size())
            throw RunnerInterrupt(msg);

        const story::Node* next = cur->get_choice(n - 1, true);
        if (!next)
            throw RunnerInterrupt(msg);

        story_->set_current(next);
    }

} // namespace libzork::runner
