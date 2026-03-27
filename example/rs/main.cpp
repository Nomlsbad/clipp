#include <algorithm>
#include <iostream>
#include <iterator>

#include <clipp/command.hpp>

namespace
{

constinit bool help = false;

constinit int count = 1;
constinit char symbol = '+';

clipp::command build_command()
{
    auto count_opt = clipp::option{"c", "count", count};
    auto symbol_opt = clipp::option{"s", "symbol", symbol};

    auto cmd = clipp::command{
    	"rs [-c COUNT] [-s SYMBOL]",
    	"repeat given symbol to stdin",
    	"repeat given symbol to stdin",
    	[]() {
    	    if (help) {
		std::cout << "Usage: rs [-c COUNT] [-s SYMBOL]\n";
		return;
	    }

	    std::ranges::fill_n(std::ostream_iterator<char>(std::cout), count, symbol);
	    std::cout << std::endl;
	},
    };

    cmd.add_option("h", "help", help);
    cmd.add_option(count_opt);
    cmd.add_option(symbol_opt);

    return cmd;
}

}

int main(int argc, const char* const argv[])
{
    auto cmd = build_command();
    cmd.run(argc, argv);

    return 0;
}
