#include <iostream>

#include <config.h>
#include <applets.hpp>

#if FALSE_BUILD == 1

int
false_main() {
    exit(ERR_CODE);
}
#endif
