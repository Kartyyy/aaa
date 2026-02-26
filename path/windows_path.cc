#include "windows_path.hh"

std::string WindowsPath::to_string() const
{
    std::string result;

    for (size_t i = 0; i < path_.size(); ++i)
    {
        result += path_[i];
        if (i + 1 < path_.size())
            result += "\\";
    }

    return result;
}
