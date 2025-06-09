
set(stargate_sources
	stargate.cpp)

add_executable(stargate ${stargate_sources})

target_link_libraries(stargate PRIVATE argparse)
