#include <minibox.hxx>

#if CLEAR_BUILD == 1

void
clear_usage() {
    std::cout << "usage: clear screen" << std::endl;
    exit(SUCC_CODE);
}

void
clear_version() {
    std::cout << MINIBOX_NAME << " " << MINIBOX_VERSION << std::endl;
    std::exit(SUCC_CODE);
}

int
clear_main(int argc, char *argv[]) {
    if (argc == 2 && (std::strcmp(argv[1], "--version") == 0)) {
        clear_version();
    } else if (argc == 2 && (std::strcmp(argv[1], "--help") == 0)) {
        clear_usage();
    } else {
        std::cout << "\033[H\033[2J\033[3J" << std::flush;
    }

    std::exit(SUCC_CODE);
}
#endif
