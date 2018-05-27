#include "AST/ASTContext.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "duktape/duktape.h"

TEST_CASE("duktape vm", "[duktape]")
{
    SECTION("vm")
    {
        duk_context *ctx = duk_create_heap_default();
        duk_eval_string(ctx, "1 + 2;");
        REQUIRE(3 == static_cast<int>(duk_get_int(ctx, -1)));
        duk_pop(ctx);
        duk_destroy_heap(ctx);
    }
}
