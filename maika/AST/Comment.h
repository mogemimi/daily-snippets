#pragma once

#include "Parser/location.hh"
#include <string>

enum class CommentKind {
    C,    // /* comment */
    BCPL, // // comment
};

struct Comment final {
    yy::location location;
    CommentKind kind;
    std::string text;

    std::string dump();
};
