#pragma once

#include <memory>

template <typename T>
class Singleton
{
public:
    static T& instance();

protected:
    Singleton() = default;
    ~Singleton() = default;

private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;

public:
    void open_log_file(const std::string& file);
    void write_to_log_file();
    void close_log_file();

private:
    Logger() = default;
};

#include "singleton.hxx"
