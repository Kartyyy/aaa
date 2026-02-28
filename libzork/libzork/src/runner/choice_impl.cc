#include "runner/choice_impl.hh"

#include <libzork/exceptions.hh>
#include <sstream>
#include <cctype>
#include <string>
#include "exceptions.hh"

namespace libzork::runner
{
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

    std::size_t n = 0;
    if (!(is_ >> n))
    {
        is_.clear();
        std::string junk;
        std::getline(is_, junk);
        throw RunnerInterrupt("invalid choice");
    }

    std::string rest;
    std::getline(is_, rest); 

    if (n < 1 || n > labels.size())
	    throw RunnerInterrupt("Please input an integer between 1 and " + std::to_string(labels.size()));

    const story::Node* next = cur->get_choice(n - 1, true);
    if (!next)
        throw RunnerInterrupt("invalid choice");

    story_->set_current(next);
}


} // namespace libzork::runner
