#include <minibox.hxx>

namespace {
    const AppletDescriptor*
    find_applet(const char* name) {
        if (!name)
            return 0;

        std::size_t count = 0;
        const AppletDescriptor* applets = applet_registry(count);

        for (std::size_t i = 0; i < count; ++i) {
            if (std::strcmp(applets[i].name, name) == 0)
                return &applets[i];
        }

        return 0;
    }
}

int
applets_call(int argc, char** argv) {
    if (argc < 2 || !argv || !argv[1])
        return ERR_CODE;

    const AppletDescriptor* applet = find_applet(argv[1]);

    if (!applet) {
        std::cerr << CMD_NOT_FOUND << ": " << argv[1] << std::endl;
        return NFOUND_CODE;
    }

    return applet->entry(argc - 1, argv + 1);
}

int
applets_as_main(int argc, char** argv) {
    if (argc < 1 || !argv || !argv[0])
        return ERR_CODE;

    const char* name = std::strrchr(argv[0], '/');
    name = name ? name + 1 : argv[0];

    const AppletDescriptor* applet = find_applet(name);

    if (!applet) {
        std::cerr << CMD_NOT_FOUND << ": " << name << std::endl;
        return NFOUND_CODE;
    }

    return applet->entry(argc, argv);
}

int
applets_list() {
    std::size_t count = 0;
    const AppletDescriptor* applets = applet_registry(count);

    for (std::size_t i = 0; i < count; ++i)
        std::cout << applets[i].name << '\n';

    return SUCC_CODE;
}
