#include <iostream>
#include <string>

#include <config.h>
#include <applets.hpp>

#if RESET_BUILD == 1

const int size = 4;
std::string validterm[size] = { "linux", "xterm", "xterm-256color", "vt100" };
const char* rterm = std::getenv("TERM");
std::string newterm;
std::string term;

void
reset_usage() {
    std::cout << "usage: reset screen" << std::endl;
    exit(SUCC_CODE);
}

void
reset_askterm() {
    int valid = 0;

    std::cerr << "reset: unknown terminal type " << term << std::endl;
    while(valid != 1) {
        std::cerr << "Terminal type? " << std::flush;
        if(!(std::cin >> newterm)) {
            std::cerr << "reset: invalid input" << std::endl;
            exit(ERR_CODE);
        }

        for(int i = 0; i < size; i++) {
            if(newterm == validterm[i]) {
                valid = 1;
                break;
            }
        }

        if(valid != 1) {
            std::cerr << "reset: unknown terminal type " << newterm << std::endl;
        }
    }
}

void
reset_term(std::string term) {
    if(term == "linux") {
        std::cout << "\033c" << std::flush;
    } else if(term == "xterm" || term == "xterm-256color") {
        std::cout << "\033c" << std::flush;
    } else if(term == "vt100") {
        std::cout << "\033c" << std::flush;
    } else {
        reset_askterm();
        reset_term(newterm);
    }
}

int
reset_main(int argc, char *argv[]) {
    if (argc == 2 && (strcmp(argv[1], "--version") == 0)) {
        version();
    } else if (argc == 2 && (strcmp(argv[1], "--help") == 0)) {
        reset_usage();
    } else {
        if(rterm != NULL) {
            term = rterm;
        } else {
            term = "unknown";
        }

        int found = 0;

        for(int i = 0; i < size; i++) {
            if(term == validterm[i]) {
                found = 1;
                break;
            }
        }

        if(found == 1) {
            reset_term(term);
        } else {
            reset_askterm();
            reset_term(newterm);
        }
    }
    exit(SUCC_CODE);
}
#endif
