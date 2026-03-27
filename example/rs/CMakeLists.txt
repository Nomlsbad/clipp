add_executable(rs)

target_sources(rs
    PRIVATE
	main.cpp
)

target_link_libraries(rs
    PRIVATE
	clipp
)

target_compile_features(rs PRIVATE cxx_std_20)
