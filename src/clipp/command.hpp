#pragma once

#include <functional>
#include <string>
#include <string_view>

#include "cmd_parsers.hpp"
#include "option.hpp"

namespace clipp
{

class command final
{
public:
    explicit command(
	std::string_view usage,
	std::string_view short_description,
	std::string_view long_description,
	std::function<void()> run
    )
    : m_usage(usage)
    , m_short_description(short_description)
    , m_long_description(long_description)
    , m_run(std::move(run))
    {}

public:

    command& add_option(option o)
    {
    	m_opts.try_emplace("-" + o.short_name(), o);
    	m_opts.try_emplace("--" + o.long_name(), o);
    	return *this;
    }

    template <typename ...Args>
    command& add_option(Args&& ...args)
    {
    	auto o = option{std::forward<Args>(args)...};
    	return add_option(std::move(o));
    }

    void run(int argc, const char* const argv[])
    {
    	auto args = parse(argc, argv);

	auto arg_it = args.begin();
    	auto end = args.cend();
    	for (; arg_it != end; ++arg_it) {
    	    auto opt_it = m_opts.find(*arg_it);
    	    if (opt_it == m_opts.cend()) {
    	    	continue;
	    }

	    auto& [_, opt] = *opt_it;
	    opt.set(*(++arg_it));
	}

    	m_run();
    }

public:

    std::string usage() const
    {
    	return m_usage;
    }

private:
    std::string m_usage;
    std::string m_short_description;
    std::string m_long_description;

    std::unordered_map<std::string, option> m_opts;

    std::function<void()> m_run;
};

} // namespace clipp
