#include <stdlib.h>
#include <iostream>

#include <argparse/argparse.hpp>

#define DARK_TOOL_NAME "dark"

int main(int argc, char** argv) {
    argparse::ArgumentParser argParser(DARK_TOOL_NAME);

    try {
        argParser.parse_args(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cerr << argParser;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
