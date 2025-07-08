set(nl_sources
    Design.cpp
    Library.cpp
    SGCDB.cpp
    Instance.cpp
)

add_library(sgc_nl_s STATIC ${nl_sources})

target_include_directories(sgc_nl_s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sgc_nl_s PRIVATE sgc_common_s)
