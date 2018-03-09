#include "ASTContext.h"
#include "ASTDumper.h"
#include "Entity.h"
#include "MyDriver.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("Lexer", "[lexer]")
{
    constexpr auto source = R"(
function min() {
    if (c == b) {
		a = b;
	}
	else if (a) {
		b;
	}
	else {
		return a;
	}

	while (a) {
		a;
		a = c;
		if (c = a) {
			let b = c;			
		}
		else {
			let a = c;
		}
	}

	for (let i = 0; i != 4; i = add(i)) {
	}
}
)";

    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source);
	REQUIRE(ok);

    {
        ASTDumper dumper;
        ASTTraverser traverser;
        traverser.traverse(astContext, dumper);
        printf("%s\n", dumper.getResult().c_str());
    }
}
