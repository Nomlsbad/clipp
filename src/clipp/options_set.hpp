#pragma once

#include <any>
#include <optional>
#include <string>
#include <unordered_map>

#include "option.hpp"

namespace clipp
{

class options_set final
{
public:

    template <typename T>
    void set(option o, T value)
    {
    	o.set(value);
    }

    template <typename T>
    std::optional<T> find(std::string_view name) const
    {
    	auto opt_it = m_options.find(name);
    	if (opt_it == m_options.cend()) {
	    return std::nullopt;
	}

	auto& [_, value] = *opt_it;
	if (!value.has_value()) {
	    return std::nullopt;
	}

	return std::any_cast<T>(value);
    }

private:
    struct string_hash
    {
	using hash_type = std::hash<std::string_view>;
	using is_transparent = void;
    
	std::size_t operator()(const char* str) const        { return hash_type{}(str); }
	std::size_t operator()(std::string_view str) const   { return hash_type{}(str); }
	std::size_t operator()(const std::string& str) const { return hash_type{}(str); }
    };

    std::unordered_map<std::string, std::any, string_hash, std::equal_to<>> m_options;
};

} // namespace clipp
