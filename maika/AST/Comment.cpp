#include "Comment.h"
#include <sstream>

std::string Comment::dump() const
{
    auto style = [&]() -> std::string {
        switch (kind) {
        case CommentKind::BCPL: return "BCPL";
        case CommentKind::C: return "C";
        }
        return "<unknown>";
    }();
    std::stringstream ss;
    ss << location.toString() << ": Comment Style = " << style << "\n" << text;
    return ss.str();
}
