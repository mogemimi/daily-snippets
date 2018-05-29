#include "AST/ASTContext.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

namespace {
std::string trimComment(CommentKind kind, const std::string& s)
{
    auto comment = Comment::make(Location{}, CommentKind::Line, s);
    return comment->getText();
}
} // end of anonymous namespace

TEST_CASE("comments", "[parser]")
{
    SECTION("comment")
    {
        REQUIRE(trimComment(CommentKind::Line, "// Hello world!") == "Hello world!");
        REQUIRE(trimComment(CommentKind::Line, "//// Hello world! \t  \t ") == "// Hello world!");
        REQUIRE(trimComment(CommentKind::Block, "/* Hello world! \t  \t */") == "Hello world!");
        REQUIRE(trimComment(CommentKind::Block, "/* Hello \t \nworld! \t */") == "Hello\nworld!");
    }
}
