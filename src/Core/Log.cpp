#include "Core/Log.hpp"

Log::Log() : str("\n") {}

void Log::AddLog(const std::string& str)
{
    this -> str += (str + '\n');
}

void Log::Clear()
{
    str.clear();
}

const char* Log::operator()() const
{
    return str.c_str();
}