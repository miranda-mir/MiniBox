#include <minibox.hxx>

namespace {
    int clear_usage() {
        std::cout << "usage: clear screen" << std::endl;
        return SUCC_CODE;
    }
}

int
clear_main(int argc, char* argv[]) {
    if (argc == 2 && std::strcmp(argv[1], "--version") == 0)
        return minibox_version();

    if (argc == 2 && std::strcmp(argv[1], "--help") == 0)
        return clear_usage();

    std::cout << "\033[H\033[2J\033[3J" << std::flush;
    return SUCC_CODE;
}
