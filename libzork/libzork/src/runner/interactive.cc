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

        os_ << cur->get_text();
        if (!cur->get_text().empty() && cur->get_text().back() != '\n')
            os_ << '\n';
    }

    void InteractiveRunner::run()
    {
        while (true)
        {
		print_script();
        os_ << "> " << std::flush;

        try
        {
            process_input();
        }
        catch (const RunnerInterrupt& e)
        {
            os_ << e.what() << "\n";
        }
        catch (const RunnerQuit&)
        {
            break; // end
        }

        if (!is_)
            break;

        os_ << '\n';
        }
    }

} // namespace libzork::runner
