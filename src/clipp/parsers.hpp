#pragma once

#include <algorithm>
#include <array>
#include <charconv>
#include <concepts>
#include <string_view>

namespace clipp
{

template <typename T>
constexpr void parse_value(std::string_view value_str, T& value) = delete;

template <std::integral T>
constexpr void parse_value(std::string_view value_str, T& value)
{
    std::from_chars(value_str.cbegin(), value_str.cend(), value);
}

constexpr void parse_value(std::string_view value_str, bool& value)
{
    constexpr auto true_values = std::to_array<std::string_view>(
	    {"t", "true", "True", "TRUE", "1"}
    );
    constexpr auto false_values = std::to_array<std::string_view>(
	    {"f", "false", "False", "FALSE", "0"}
    );

    if (std::ranges::find(true_values, value_str) != true_values.cend()) {
    	value = true;
    	return;
    }

    if (std::ranges::find(false_values, value_str) != false_values.cend()) {
    	value = false;
    	return;
    }

    std::abort();
}

constexpr void parse_value(std::string_view value_str, char& value)
{
    value = value_str[0];
}

}
