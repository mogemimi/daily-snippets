#pragma once

#include "Basic/Location.h"
#include <string>

enum class CommentKind {
    C,    // /* comment */
    BCPL, // // comment
};

struct Comment final {
    Location location;
    CommentKind kind;
    std::string text;

    std::string dump();
};
