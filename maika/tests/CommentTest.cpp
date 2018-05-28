#include "AST/ASTContext.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("comments", "[parser]")
{
    SECTION("comment")
    {
        Comment comment;
        comment.kind = CommentKind::BCPL;
        comment.text = "////  // Hello world! \t  \t ";
        REQUIRE(comment.getText() == " // Hello world!");
    }
}
