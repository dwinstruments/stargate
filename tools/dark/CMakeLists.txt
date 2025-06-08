
set(dark_sources
	Dark.cpp)

add_executable(dark ${dark_sources})

target_link_libraries(dark PRIVATE argparse)
