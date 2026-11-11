#include <iostream>

#include <config.h>
#include <applets.hpp>

#if TRUE_BUILD == 1

int
true_main() {
    exit(SUCC_CODE);
}
#endif
