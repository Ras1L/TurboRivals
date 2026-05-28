#ifndef CORE_LOG_HPP
#define CORE_LOG_HPP

#include <string>

class Log {
public:
    Log();
    void AddLog(const std::string& str);
    void Clear();

    const char* operator()() const;

private:
    std::string str;
};

#endif