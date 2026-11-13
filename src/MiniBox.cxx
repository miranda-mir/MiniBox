#include <minibox.hxx>

namespace {
    std::size_t count = 0;
    const AppletDescriptor* applets = applet_registry(count);
    const std::size_t max_width = 80;
    const std::size_t indent = 8;
    std::size_t column = indent;

    void
    usage() {
        std::cout
            << MINIBOX_NAME << " v" << MINIBOX_VERSION << " multi-call binary.\n"
            << "Licensed under GPLv3. See source distribution for detailed\ncopyright notices.\n"
            << "\n"
            << "Usage: " << MINIBOX_BINARY_NAME << " [applet [arguments]...]\n"
            << "   or: " << MINIBOX_BINARY_NAME << " --list\n"
            << "   or: " << MINIBOX_BINARY_NAME << " --version\n"
            << "   or: " << "applet [arguments]...\n"
            << "	MiniBox is a multi-call binary alternative for BusyBox and Toybox.\n"
            << "	MiniBox does not support yet all the features present in Busybox or\n"
            << "	Toybox. MiniBox packs common UNIX CLI utilities into one single executable.\n\n"
            << "Currently available applets:\n";

    std::cout << '\t';

    for (std::size_t i = 0; i < count; ++i) {
        const char* name = applets[i].name;
        const std::size_t length = std::strlen(name);

        if (i > 0) {
            if (column + 2 + length > max_width) {
                std::cout << ",\n\t";
                column = indent;
            } else {
                std::cout << ", ";
                column += 2;
            }
        }

        std::cout << name;
        column += length;
}

std::cout << '\n';
    }
}

int
minibox_version() {
    std::cout << MINIBOX_NAME << " v" << MINIBOX_VERSION << std::endl;
    return SUCC_CODE;
}

int
main(int argc, char** argv) {
    if (argc < 1 || !argv || !argv[0])
        return ERR_CODE;

    const char *invoked_name = minibox::basename(argv[0]);

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
