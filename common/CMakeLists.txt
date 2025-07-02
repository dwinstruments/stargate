set(common_sources
    SharedString.cpp
    StringManager.cpp
)

add_library(sgc_common_s STATIC ${common_sources})

target_include_directories(sgc_common_s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})