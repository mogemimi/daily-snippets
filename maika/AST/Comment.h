#pragma once

#include "Basic/Location.h"
#include <string>

enum class CommentKind {
    Block,
    Line,
};

class Comment final {
private:
    Location location;
    CommentKind kind;
    std::string text;

public:
    Location getLocation() const;

    CommentKind getKind() const;

    std::string getText() const;

    std::string dump() const;

    static std::shared_ptr<Comment> make(Location loc, CommentKind kind, const std::string& text);
};
