#include "singleton.hh"
#include <iostream>

void Logger::open_log_file(const std::string& file)
{
    std::cout << "LOG: Opening file " << file << std::endl;
}

void Logger::write_to_log_file()
{
    std::cout << "LOG: Writing into log file ..." << std::endl;
}

void Logger::close_log_file()
{
    std::cout << "LOG: Closing log file ..." << std::endl;
}
