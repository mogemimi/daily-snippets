#include "AST.h"
#include "Entity.h"
#include "IdentifierResolver.h"
#include "TypeResolver.h"
#include "MyLexer.h"
#include "MyDriver.h"
#include <iostream>
#include <sstream>

int main()
{
    MyDriver driver;

    constexpr auto filename = "/Volumes/marie/daily-snippets/maika/examples/hoge.ts";
    auto [result, ok] = driver.parse(filename);
    if (ok) {
        printf("%s\n", result.c_str());
    } else {
        printf("parse error\n");
        return 1;
    }

    IdentifierContext context;
    {
        IdentifierResolver resolver(&context);
        ASTTraverser traverser;
        traverser.traverse(driver.ast, resolver);
    }

    TypeResolver typeResolver;
    {
        ASTTraverser traverser;
        traverser.traverse(driver.ast, typeResolver);
    }
    return 0;
}
