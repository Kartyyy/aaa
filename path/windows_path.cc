#include "windows_path.hh"


Path& WindowsPath::join(const std::string& tail, bool is_file)
{
    if (final_ || tail.empty())
        return *this;

    const std::string forbidden = "*?:|\"<>";

    for (char c : tail)
        if (forbidden.find(c) != std::string::npos)
            return *this; 

    path_.push_back(tail);
    final_ = is_file;
    return *this;
}

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
