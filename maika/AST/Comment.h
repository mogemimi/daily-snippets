#pragma once

#include "Basic/Location.h"
#include <string>

enum class CommentKind {
    C,    // /* comment */
    BCPL, // // comment
};

class Comment final {
public:
    Location location;
    CommentKind kind;
    std::string text;

public:
    std::string getText() const;

    std::string dump() const;
};
