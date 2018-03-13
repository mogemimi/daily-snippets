#include "Comment.h"
#include <sstream>

std::string Comment::dump()
{
    auto style = [&]() -> std::string {
        switch (kind) {
        case CommentKind::BCPL: return "BCPL";
        case CommentKind::C: return "C";
        }
    }();
    std::stringstream ss;
    ss << location << ": Comment Style = " << style << "\n" << text;
    return ss.str();
}
