#pragma once

#include <functional>
#include <memory>
#include <string>
#include <string_view>

#include "parsers.hpp"

namespace clipp
{

class option final
{
public:
    template <typename T>
    explicit option(
    	std::string_view short_name,
    	std::string_view long_name,
    	T& value
    )
    : m_short_name(short_name)
    , m_long_name(long_name)
    , m_value_ptr(std::addressof(value))
    , m_parse([](std::string_view value_str, void* p) { parse_value(value_str, *static_cast<T*>(p)); })
    {}

public:
    std::string short_name() const
    {
    	return m_short_name;
    }

    std::string long_name() const
    {
    	return m_long_name;
    }

    void set(std::string_view value_str)
    {
    	m_parse(value_str, m_value_ptr);
    }

private:
    std::string m_short_name;
    std::string m_long_name;

    void* m_value_ptr;
    std::function<void(std::string_view, void*)> m_parse;
};

} // namespace clipp
