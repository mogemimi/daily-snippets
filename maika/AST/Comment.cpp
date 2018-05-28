#include "Comment.h"
#include "Basic/StringHelper.h"
#include <sstream>

std::string Comment::getText() const
{
    auto s = text;

    if (kind == CommentKind::BCPL) {
        s = StringHelper::trimLeft(s, '/');
        if ((s.size() >= 1) && (s.front() == ' ')) {
            s.erase(s.begin());
        }
        s = StringHelper::trimRight(s, [](char c) -> bool { return isspace(c); });
    }

    return s;
}

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
