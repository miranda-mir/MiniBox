#ifndef MINIBOX_HXX
#define MINIBOX_HXX

#include "MiniBoxConfig.h"
#include "applets.hxx"
#include "appletRegistry.hxx"
#include "exitCodes.hxx"
#include "outputmsg.hxx"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef MINIBOX_VERSION
#define MINIBOX_VERSION "Unknown"
#endif

namespace minibox {
    char *basename(const char* path);
}

#endif
