#include <minibox.hxx>

namespace minibox {
    char*
    basename(const char* path) {
        if (path == 0)
            return 0;

        const char* name = std::strrchr(path, '/');

        if (name != 0)
            ++name;
        else
            name = path;

        char* result = new char[std::strlen(name) + 1];
        std::strcpy(result, name);

        return result;
    }
}
