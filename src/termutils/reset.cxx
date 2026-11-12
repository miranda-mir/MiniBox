#include <minibox.hxx>

namespace {
    const char* const
    valid_terms[] = {
        "linux",
        "xterm",
        "xterm-256color",
        "vt100"
    };

    bool
    is_valid_term(const std::string& term) {
        const std::size_t count =
            sizeof(valid_terms) / sizeof(valid_terms[0]);

        for (std::size_t i = 0; i < count; ++i) {
            if (term == valid_terms[i])
                return true;
        }

        return false;
    }

    int
    reset_usage() {
        std::cout << "usage: reset screen" << std::endl;
        return SUCC_CODE;
    }

    int
    ask_terminal(std::string& selected, const std::string& current) {
        std::cerr << "reset: unknown terminal type " << current << std::endl;

        while (true) {
            std::cerr << "Terminal type? " << std::flush;

            if (!(std::cin >> selected)) {
                std::cerr << "reset: invalid input" << std::endl;
                return ERR_CODE;
            }

            if (is_valid_term(selected))
                return SUCC_CODE;

            std::cerr << "reset: unknown terminal type " << selected << std::endl;
        }
    }

    int reset_terminal(const std::string& term) {
        if (is_valid_term(term)) {
            std::cout << "\033c" << std::flush;
            return SUCC_CODE;
        }

        std::string selected;
        const int status = ask_terminal(selected, term);

        if (status != SUCC_CODE)
            return status;

        return reset_terminal(selected);
    }
}

int
reset_main(int argc, char* argv[]) {
    if (argc == 2 && std::strcmp(argv[1], "--version") == 0)
        return minibox_version();

    if (argc == 2 && std::strcmp(argv[1], "--help") == 0)
        return reset_usage();

    const char* environment_term = std::getenv("TERM");
    const std::string term = environment_term ? environment_term : "unknown";

    return reset_terminal(term);
}
