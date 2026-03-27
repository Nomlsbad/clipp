add_library(clipp INTERFACE)

target_sources(clipp
    INTERFACE
	FILE_SET HEADERS
	FILES
	    clipp/cmd_parsers.hpp
	    clipp/command.hpp
	    clipp/option.hpp
	    clipp/options_set.hpp
	    clipp/parsers.hpp
)

target_compile_features(clipp INTERFACE cxx_std_20)
