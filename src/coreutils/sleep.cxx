#include <minibox.hxx>

namespace {
    void
    sleep_usage() {
        std::cout << "usage: sleep [TIME]" << std::endl;
    }
}

int
sleep_main(int argc, char* argv[]) {
    int time;

    if (argc == 2 && std::strcmp(argv[1], "--version") == 0)
        return minibox_version();

    if (argc == 2 && std::strcmp(argv[1], "--help") == 0) {
        sleep_usage();
        return SUCC_CODE;
    }

    if(argc < 2) {
        std::cerr << MISSING_OPR << std::endl;
        std::exit(ERR_CODE);
    }

    time = std::atoi(argv[1]);

    if(time < 0) {
        std::cerr << INVALID_OPT << ": " << argv[1] << std::endl;
        std::exit(ERR_CODE);
    }

    sleep(time);
    std::exit(SUCC_CODE);
}
