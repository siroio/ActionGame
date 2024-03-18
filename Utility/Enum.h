#pragma once
#include <concepts>

template<class T>
concept EnumClass = std::is_enum_v<T>;

template<EnumClass T>
class Enum
{
private:
    using value_type = std::underlying_type_t<T>;
    using enum_type = T;

public:
    Enum() = default;
    Enum(value_type val) : value(static_cast<T>(val))
    {}

    value_type Value() const
    {
        return value;
    }

    explicit operator T() const
    {
        return value;
    }

    Enum& operator=(const value_type& val)
    {
        value = static_cast<T>(val);
        return *this;
    }

    operator value_type() const
    {
        return static_cast<value_type>(value);
    }

    bool operator==(const Enum<enum_type>& other) const
    {
        return value == other.value;
    }

    bool operator==(const enum_type& other) const
    {
        return value == other;
    }

    bool operator==(const value_type& other) const
    {
        return value == static_cast<T>(other);
    }

    bool operator!=(const Enum<enum_type>& other) const
    {
        return value != other.value;
    }

    bool operator!=(const enum_type& other) const
    {
        return value != other;
    }

    bool operator!=(const value_type& other) const
    {
        return value != static_cast<T>(other);
    }
private:
    T value;
};
