#include "Core/EasyBytes.hpp"

EasyBytes::EasyBytes() : buffer(), offset(0) {}

EasyBytes::EasyBytes(const void* data, size_type size)
{
    buffer.resize(size);
    std::memcpy(buffer.data(), data, size);
    offset = 0;
}

EasyBytes::EasyBytes(const EasyBytes& rhs) = default;
EasyBytes EasyBytes::operator=(const EasyBytes& rhs)
{
    std::memcpy(buffer.data(), rhs.buffer.data() + offset, rhs.buffer.size());
    return *this;
}

EasyBytes::EasyBytes(EasyBytes&& rhs) noexcept = default;
EasyBytes EasyBytes::operator=(EasyBytes&& rhs) noexcept
{
    std::memcpy(buffer.data(), rhs.buffer.data() + offset, rhs.buffer.size());

    rhs.buffer.clear();
    rhs.offset = 0;
    
    return *this;
}

EasyBytes::~EasyBytes() noexcept = default;

const void* EasyBytes::Data() const
{
    return buffer.data();
}

EasyBytes::size_type EasyBytes::Size() const
{
    return buffer.size();
}

void EasyBytes::ResetOffset() const
{
    offset = 0;
}

void EasyBytes::Clear()
{
    buffer.clear();
}