#ifndef MINIBOX_APPLET_REGISTRY_HXX
#define MINIBOX_APPLET_REGISTRY_HXX

#include <cstddef>

struct AppletDescriptor {
    const char* name;
    int (*entry)(int, char**);
};

const AppletDescriptor* applet_registry(std::size_t& count);

#endif
