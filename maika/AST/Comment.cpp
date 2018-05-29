#include "Comment.h"
#include "Basic/StringHelper.h"
#include <cassert>
#include <sstream>

Location Comment::getLocation() const
{
    return location;
}

CommentKind Comment::getKind() const
{
    return kind;
}

std::string Comment::getText() const
{
    auto s = text;

    if (s.size() >= 2) {
        switch (s[1]) {
        case '/':
            // BCPL-style line comment
            assert(s[0] == '/');
            s.erase(s.begin(), s.begin() + 2);
            break;
        case '*':
            /* C-style block comment */
            assert(s.size() >= 4);
            assert(s[0] == '/');
            assert(s[s.size() - 2] == '*');
            assert(s[s.size() - 1] == '/');
            s.erase(s.begin(), s.begin() + 2);
            s.erase(s.end() - 2, s.end());
            break;
        default: break;
        }
    }

    if ((s.size() >= 1) && isspace(s.front())) {
        s.erase(s.begin());
    }

    auto lines = StringHelper::split(s, '\n');
    for (auto& line : lines) {
        line = StringHelper::trimRight(line, [](char c) -> bool { return isspace(c); });
    }
    return StringHelper::join(lines, '\n');
}

std::string Comment::dump() const
{
    auto style = [&]() -> std::string {
        switch (kind) {
        case CommentKind::Line: return "Line";
        case CommentKind::Block: return "Block";
        }
        return "<unknown>";
    }();
    std::stringstream ss;
    ss << location.toString() << ": Comment Style = " << style << "\n" << text;
    return ss.str();
}

std::shared_ptr<Comment> Comment::make(Location loc, CommentKind kind, const std::string& text)
{
    auto comment = std::make_shared<Comment>();
    comment->location = loc;
    comment->kind = kind;
    comment->text = text;
    return comment;
}
