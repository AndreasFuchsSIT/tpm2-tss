/* SPDX-License-Identifier: BSD-2-Clause */

#include <fcntl.h>

#define LOGMODULE tests
#include "util/log.h"

int wrap_visited = 0;

int
__wrap_open(const char *pathname, int flags, ...)
{
    (void)(pathname); (void)(flags);
    wrap_visited++;
    return 1234;
}

int
main(int argc, char* argv[])
{
    if (open("DummyFilenameThatMustNotExist", 0) != 1234 || !wrap_visited) {
        LOG_ERROR("Your compiler seems to not support the -Wl,--wrap methods.");
        LOG_ERROR("This will lead to a lot of false-negative tests.");
        return 99;
    }
    return 0;
}
