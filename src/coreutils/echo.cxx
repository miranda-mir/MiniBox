#include <minibox.hxx>

namespace {
    void
    echo_usage() {
        std::cout << "usage: echo [OPTION]... [STRING]..." << std::endl;
    }

    void
    option_manager(const char* option, bool& newline, bool& interpretation) {
        if (std::strcmp(option, "-") == 0) {
            std::cout << option;
        } else if (std::strcmp(option, "-n") == 0) {
            newline = false;
        } else if (std::strcmp(option, "-e") == 0) {
            interpretation = true;
        } else if (std::strcmp(option, "-E") == 0) {
            interpretation = false;
        }
    }

    void
    just_echo(const char* text) {
        std::cout << text << " ";
    }
}

int
echo_main(int argc, char* argv[]) {
    bool newline = true;
    bool interpretation = false;

    if (argc == 2 && std::strcmp(argv[1], "--version") == 0)
        return minibox_version();

    if (argc == 2 && std::strcmp(argv[1], "--help") == 0) {
        echo_usage();
        return SUCC_CODE;
    }

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-')
            option_manager(argv[i], newline, interpretation);
        else
            just_echo(argv[i]);
    }

    if (newline)
        std::cout << '\n';

    return SUCC_CODE;
}
