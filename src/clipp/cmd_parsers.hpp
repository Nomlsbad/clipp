#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace clipp
{

class cmd_parser final
{
public:
    explicit cmd_parser(int argc, const char* const argv[])
    {
    	m_args.resize(argc);
	std::ranges::copy(argv, argv + argc, m_args.begin());
    }

public:
    std::vector<std::string> parse() const
    {
    	return m_args;
    }

private:
    std::vector<std::string> m_args;
};

inline std::vector<std::string> parse(int argc, const char* const argv[])
{
    return cmd_parser{argc, argv}.parse();
}

} // namespace clipp
