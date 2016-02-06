// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "TerminalHelper.h"
#include <cassert>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

namespace somera {

std::string getHomeDirectory()
{
    auto home = ::getenv("HOME");
    if (home == nullptr) {
        auto pw = ::getpwuid(::getuid());
        assert(pw != nullptr);
        home = pw->pw_dir;
    }
    return std::move(home);
}

} // namespace somera
