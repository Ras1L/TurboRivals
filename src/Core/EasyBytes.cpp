#include "Core/EasyBytes.hpp"

EasyBytes::EasyBytes() : buffer(), offset(0) {}

EasyBytes::EasyBytes(const void* data, size_type size)
{
    buffer.resize(size);
    std::memcpy(buffer.data(), data, size);
    offset = 0;
}

EasyBytes::EasyBytes(const EasyBytes& rhs) = default;
EasyBytes& EasyBytes::operator=(const EasyBytes& rhs) = default;

EasyBytes::EasyBytes(EasyBytes&& rhs) noexcept = default;
EasyBytes& EasyBytes::operator=(EasyBytes&& rhs) noexcept = default;

EasyBytes::~EasyBytes() noexcept = default;

EasyBytes EasyBytes::Read() const
{
    EasyBytes bytes;
    
    auto new_size = buffer.size() - offset;
    bytes.buffer.resize(new_size);
    std::memcpy(bytes.buffer.data(), buffer.data() + offset, new_size);

    return bytes;
}

void EasyBytes::Write(const void* data, size_type data_size)
{
    auto old_size = buffer.size();
    buffer.resize(old_size + data_size);
    std::memcpy(buffer.data() + old_size, data, data_size);
}

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
    offset = 0;
}