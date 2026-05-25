#ifndef CORE_EASY_BYTES_HPP
#define CORE_EASY_BYTES_HPP

#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

/// Работает только с простыми типами и POD-типами
class EasyBytes {
public:
    using bytes_type = std::vector<std::uint8_t>;
    using size_type  = std::size_t;

public:
    EasyBytes();
    EasyBytes(const void* data, size_type size);

    EasyBytes(const EasyBytes& rhs);
    EasyBytes operator=(const EasyBytes& rhs);
    
    EasyBytes(EasyBytes&& rhs) noexcept;
    EasyBytes operator=(EasyBytes&& rhs) noexcept;

    ~EasyBytes() noexcept;

    const void* Data() const; // для связи с Enet, может и не только
    size_type   Size() const;

    /// ResetOffset after some Read.
    void ResetOffset() const;

    /// Clear before some Write.
    void Clear();

    template <class T>
    requires std::is_trivially_copyable_v<T>
    T Read() const
    {
        T value;
        auto value_size = sizeof(T);
        std::memcpy(&value, buffer.data() + offset, value_size);
        offset += value_size;
        return value;
    }

    template <class T>
    requires std::is_trivially_copyable_v<T>
    void Write(const T& value)
    {
        auto old_size = buffer.size();
        auto value_size = sizeof(T);
        buffer.resize(old_size + value_size);
        std::memcpy(buffer.data() + old_size, &value, value_size);
    }

    template <class... Args>
    requires std::is_trivially_copyable_v<Args...>
    void WriteAll(Args&&... args)
    {
        Clear();
        (Write(args), ...); // std::forward и перемещения не имеют смысла если работать с массивом байт
    }

private:
    bytes_type        buffer;
    mutable size_type offset; // только для чтения
};

#endif