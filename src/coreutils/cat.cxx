/*
 * Copyright (C) 2026 Pietro Carlini
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <minibox.hxx>

namespace {}
    void
    cat_usage() {
        std::cout << "cat [OPTION] [FILE]" << std::endl;
        std::cout << " -n Numbers all lines" << std::endl;
        std::cout << " -u Does not use buffer at output" << std::endl;
    }

    char*
    getArg(int argc, char **argv, const char *arg, int value) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], arg) != 0)
                continue;

            if (value && i + 1 < argc)
                return argv[i + 1];

            return (char *)1;
        }

        return 0;
}


int
cat_main(int argc, char **argv) {
     if (argc == 2 && std::strcmp(argv[1], "--version") == 0)
        return minibox_version();

     if (argc == 2 && std::strcmp(argv[1], "--help") == 0) {
        cat_usage();
        return SUCC_CODE;
     }

    char *n = getArg(argc, argv, "-n", 0);
    char *u = getArg(argc, argv, "-u", 0);

    if (u)
        setbuf(stdout, NULL);

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-')
            continue;

        FILE *file = fopen(argv[i], "r");

        if (!file)
            return ERR_CODE;

        int c;
        int line = 1;
        int start = 1;

        while ((c = fgetc(file)) != EOF) {
            if (start && n) {
                std::cout << " \033[F" << line << std::endl;
                line++;
                start = 0;
            }

            if (u)
                putchar(c);
            else
                putchar(c);

            if (c == '\n')
                start = 1;
        }

        fclose(file);
    }

    return SUCC_CODE;
}
