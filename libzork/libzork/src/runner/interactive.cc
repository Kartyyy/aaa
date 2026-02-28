#include <libzork/exceptions.hh>
#include <libzork/runner/interactive.hh>

#include "exceptions.hh"

namespace libzork::runner
{
    InteractiveRunner::InteractiveRunner(std::unique_ptr<story::Story> story,
                                         std::istream& is, std::ostream& os)
        : Runner(std::move(story))
        , is_(is)
        , os_(os)
    {}

    void InteractiveRunner::print_script() const
{
    const story::Node* cur = story_->get_current();
    if (!cur)
        return;

    const std::string& txt = cur->get_text();
    os_ << txt;
    if (!txt.empty() && txt.back() != '\n')
        os_ << '\n';
}

void InteractiveRunner::run()
{
    while (true)
    {
        const story::Node* cur = story_->get_current();
        if (!cur)
            break;

        print_script();

        // end node
        if (cur->list_choices(true).empty())
        {
            os_ << '\n';
            break;
        }

        os_ << '\n'; // empty line before prompt/choices

        while (true)
        {
            os_ << "> " << std::flush;

            try
            {
                process_input();
                os_ << '\n';
                break;
            }
            catch (const RunnerInterrupt& e)
            {
                os_ << "\n[bad input] " << e.what() << "\n";
            }
            catch (const RunnerQuit&)
            {
                os_ << '\n';
                return;
            }

            if (!is_)
                return;
        }
    }
}}
