#include <minibox.hxx>

namespace {
    const char*
    program_basename(const char* path) {
        const char* slash = std::strrchr(path, '/');
        return slash ? slash + 1 : path;
    }

    void
    usage() {
        std::cout
            << "Usage:\n"
            << MINIBOX_BINARY_NAME << " --version\n"
            << MINIBOX_BINARY_NAME << " --help\n"
            << MINIBOX_BINARY_NAME << " --list\n"
            << MINIBOX_BINARY_NAME << " command [[arguments]...]\n\n"
            << "MiniBox is a multicall utility.\n";
    }
}

int
minibox_version() {
    std::cout << MINIBOX_NAME << " " << MINIBOX_VERSION << std::endl;
    return SUCC_CODE;
}

int
main(int argc, char** argv) {
    if (argc < 1 || !argv || !argv[0])
        return ERR_CODE;

    const char* invoked_name = program_basename(argv[0]);

    if (std::strcmp(invoked_name, MINIBOX_BINARY_NAME) != 0)
        return applets_as_main(argc, argv);

    if (argc == 1 ||
        (argc == 2 && std::strcmp(argv[1], "--help") == 0)) {
        usage();
        return SUCC_CODE;
    }

    if (argc == 2 && std::strcmp(argv[1], "--version") == 0)
        return minibox_version();

    if (argc == 2 && std::strcmp(argv[1], "--list") == 0)
        return applets_list();

    return applets_call(argc, argv);
}
