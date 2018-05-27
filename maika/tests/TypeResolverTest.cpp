#include "Sema/TypeResolver.h"
#include "AST/ASTContext.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/SemaChecker.h"
#include "Sema/TypeInferer.h"

#include "catch.hpp"

namespace {
bool typeCheck(
    const std::shared_ptr<DiagnosticHandler>& diag,
    const std::string& source,
    ASTContext& astContextOut,
    IdentifierContext& context)
{
    Driver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    REQUIRE(ok);
    astContextOut = astContext;

    ASTTraverser traverser;

    IdentifierResolver resolver(&context, diag);
    traverser.traverse(astContext, resolver);
    REQUIRE(!diag->hasError());

    SemaChecker semaChecker(diag);
    traverser.traverse(astContext, semaChecker);
    REQUIRE(!diag->hasError());

    TypeResolver typeResolver(diag);
    traverser.traverse(astContext, typeResolver);
    return !diag->hasError();
}

bool requireType(
    const IdentifierContext& context, const std::string& name, const std::string& expect)
{
    auto iter = std::find_if(
        std::begin(context.entities),
        std::end(context.entities),
        [&](const std::shared_ptr<Entity>& a) -> bool { return a->getName() == name; });
    REQUIRE(iter != std::end(context.entities));

    auto entity = *iter;
    REQUIRE(entity->getDecl() != nullptr);

    auto actual = entity->getDecl()->getType();
    REQUIRE(actual);

    if (actual->getKind() == TypeKind::TypeVariable) {
        return "Any" == expect;
    }

    return actual->dump() == expect;
}
} // end of anonymous namespace

TEST_CASE("TypeResolver can detect type mismatch", "[typecheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    ASTContext astContext;
    IdentifierContext context;

    SECTION("Type 'Int' is not assignable to 'String'.")
    {
        constexpr auto source = R"(func test() {
            let a = "a";
            a = 2;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "String"));
        REQUIRE(stream->hasError("error: Type 'Int' is not assignable to 'String'."));
    }
    SECTION("Implicit type conversion: Int to Double")
    {
        constexpr auto source = R"(func test() {
            let a = 2.0;
            a = 2;
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("Type 'Double' is not assignable to 'Int'.")
    {
        constexpr auto source = R"(func test() {
            let a = 2;
            a = 2.0;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(stream->hasError("error: Type 'Double' is not assignable to 'Int'."));
    }
    SECTION("Type 'Int' is not assignable to 'Bool'.")
    {
        constexpr auto source = R"(func test() {
            let a = true;
            a = 1;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(stream->hasError("error: Type 'Int' is not assignable to 'Bool'."));
    }
    SECTION("Type 'Bool' is not assignable to 'Double'")
    {
        constexpr auto source = R"(func test() {
            let a = 1.0;
            a = true;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(stream->hasError("error: Type 'Bool' is not assignable to 'Double'."));
    }
    SECTION("Implicit type conversion: Int to Double")
    {
        constexpr auto source = R"(func test() {
            let a = 1.0;
            a = 1;
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("Implicit type conversion: Int to Double")
    {
        constexpr auto source = R"(func test() {
            return 10 + 4.2;
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("Operator '+' cannot be applied to types 'Int' and 'String'")
    {
        constexpr auto source = R"(func test() {
            let a = 10 + "hello";
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(
            stream->hasError("error: Operator '+' cannot be applied to types 'Int' and 'String'."));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        func f() { return 42; }
        func test() {
            let a = 3;
            a = f();
        }
        )";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        func f() { return 42; }
        func test() {
            let a = "hello";
            a = f();
        }
        )";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(stream->hasError("error: Type 'Int' is not assignable to 'String'."));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        func f(x) { return x; }
        func test() { return f(2.0) + 3.14; }
        )";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        func f(x) { return x; }
        func test() { return 3.14 + f(2.0); }
        )";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("Type 'Int' is not callable.")
    {
        constexpr auto source = R"(func f() {
            let a = 42;
            a();
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Int"));
        REQUIRE(stream->hasError("error: Cannot call a non-function whose type is 'Int'."));
    }
    SECTION("Type 'Double' is not callable.")
    {
        constexpr auto source = R"(func f() {
            let a = 3.14;
            a();
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Double"));
        REQUIRE(stream->hasError("error: Cannot call a non-function whose type is 'Double'."));
    }
    SECTION("Type 'Bool' is not callable.")
    {
        constexpr auto source = R"(func f() {
            let a = true;
            a();
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Bool"));
        REQUIRE(stream->hasError("error: Cannot call a non-function whose type is 'Bool'."));
    }
    SECTION("Type 'String' is not callable.")
    {
        constexpr auto source = R"(func f() {
            let a = "hello";
            a();
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "String"));
        REQUIRE(stream->hasError("error: Cannot call a non-function whose type is 'String'."));
    }
    SECTION("Type 'null' is not callable.")
    {
        constexpr auto source = R"(func f() {
            let a = null;
            a();
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "null"));
        REQUIRE(stream->hasError("error: Cannot call a non-function whose type is 'null'."));
    }
    SECTION("Type 'Any' is callable.")
    {
        constexpr auto source = R"(func f() {
            let a;
            a();
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Any"));
    }
    SECTION("Type 'Array' is not callable.")
    {
        constexpr auto source = R"(func f() {
            let a = [];
            a();
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Array"));
        REQUIRE(stream->hasError("error: Cannot call a non-function whose type is 'Array'."));
    }
    SECTION("Type 'Map' is not callable.")
    {
        constexpr auto source = R"(func f() {
            let a = [:];
            a();
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Map"));
        REQUIRE(stream->hasError("error: Cannot call a non-function whose type is 'Map'."));
    }
    SECTION("Operator '+' cannot be applied to types 'String' and 'Double'.")
    {
        constexpr auto source = R"(
        func f(x) { return x; }
        func test() { return "hello" + f(2.0); }
        )";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(stream->hasError(
            "error: Operator '+' cannot be applied to types 'String' and 'Double'."));
    }
    SECTION("Operator '+' cannot be applied to types 'Double' and 'String'.")
    {
        constexpr auto source = R"(
        func f(x) { return x; }
        func test() { return f(2.0) + "hello"; }
        )";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("Use modulus on integer")
    {
        constexpr auto source = R"(func test() { 10 % 3; })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("invalid operands of types 'Double' and 'Double' to binary 'operator%'.")
    {
        constexpr auto source = R"(func test() { 42 % 3.14; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(
            stream->hasError("error: invalid operands to binary expression ('Int' and 'Double')."));
    }
    SECTION("invalid operands of types 'Double' and 'Double' to binary 'operator%'.")
    {
        constexpr auto source = R"(func test() { 3.14 % 42; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(
            stream->hasError("error: invalid operands to binary expression ('Double' and 'Int')."));
    }
    SECTION("invalid operands of types 'Double' and 'Double' to binary 'operator%'.")
    {
        constexpr auto source = R"(func f(x) { x % 3.14; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(
            stream->hasError("error: invalid operands to binary expression ('Any' and 'Double')."));
    }
    SECTION("invalid operands of types 'Bool' and 'Bool' to binary 'operator%'.")
    {
        constexpr auto source = R"(func test() { 42 % true; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(
            stream->hasError("error: invalid operands to binary expression ('Int' and 'Bool')."));
    }
    SECTION("invalid operands of types 'Bool' and 'Bool' to binary 'operator%'.")
    {
        constexpr auto source = R"(func test() { true % 42; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(
            stream->hasError("error: invalid operands to binary expression ('Bool' and 'Int')."));
    }
    SECTION("strings can concatenate using 'operator+'")
    {
        constexpr auto source = R"(func test() { "a" + "b"; })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("invalid operands of types 'String' and 'String' to binary 'operator*'")
    {
        constexpr auto source = R"(func test() { "a" * "b"; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(stream->hasError(
            "error: invalid operands to binary expression ('String' and 'String')."));
    }
    SECTION("invalid operands of types 'String' and 'String' to binary 'operator-'")
    {
        constexpr auto source = R"(func test() { "a" - "b"; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(stream->hasError(
            "error: invalid operands to binary expression ('String' and 'String')."));
    }
}

TEST_CASE("TypeResolver can detect type mismatch for arrays and maps", "[typecheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    ASTContext astContext;
    IdentifierContext context;

    SECTION("arrays")
    {
        constexpr auto source = R"(func f() {
            let x = [];
            let y = [1, 2, 3, 4];
            let z = [42, true, 3.14, "a", null, ["a"], [1]];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "x", "Array"));
        REQUIRE(requireType(context, "y", "Array<Int>"));
        REQUIRE(requireType(context, "z", "Array"));
    }
    SECTION("maps")
    {
        constexpr auto source = R"(func f() {
            let x = [:];
            let y = ["a": 1, "b": 2, "c": 3];
            let z = ["a": 42, "b": true, "c": 3.14, "d": "foo", "e": null];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "x", "Map"));
        REQUIRE(requireType(context, "y", "Map<String, Int>"));
        REQUIRE(requireType(context, "z", "Map"));
    }
    SECTION("maps in array")
    {
        constexpr auto source = R"(func test() {
            let x = [["a": 1], ["b": 2, "c": 3]];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "x", "Array<Map<String, Int>>"));
    }
    SECTION("arrays in map")
    {
        constexpr auto source = R"(func test() {
            let x = ["a": [1, 2], "b": [3], "c": 4];
            let y = ["a": [3.14], "b": [["x": "foo"]], "c": [["y": 42], true]];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "x", "Map"));
        REQUIRE(requireType(context, "y", "Map"));
    }
    SECTION("nested empty arrays")
    {
        constexpr auto source = R"(func test() {
            let x = [[]];
            let y = [[[]]];
            let z = [[[]], []];
            let w = [[[]], [[], []], [[[], []], []]];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "x", "Array<Array>"));
        REQUIRE(requireType(context, "y", "Array<Array<Array>>"));
        REQUIRE(requireType(context, "z", "Array"));
        REQUIRE(requireType(context, "w", "Array"));
    }
    SECTION("maps included an empty one, in array")
    {
        constexpr auto source = R"(func test() {
            let x = [[], ["a": 1], ["b": 2, "c": 3]];
            let y = [["a": 1], ["b": 2, "c": 3], []];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "x", "Array"));
        REQUIRE(requireType(context, "y", "Array"));
    }
    SECTION("Int is not assignable to array")
    {
        constexpr auto source = R"(func f() {
            let a = [42];
            a = 42;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Array<Int>"));
    }
    SECTION("Double is not assignable to array")
    {
        constexpr auto source = R"(func f() {
            let a = [42];
            a = 3.14;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("Bool is not assignable to array")
    {
        constexpr auto source = R"(func f() {
            let a = [42];
            a = true;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("String is not assignable to array")
    {
        constexpr auto source = R"(func f() {
            let a = [42];
            a = "foo";
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("Int is not assignable to map")
    {
        constexpr auto source = R"(func f() {
            let x = ["a": 42];
            x = 42;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("Int is not assignable to map")
    {
        constexpr auto source = R"(func f() {
            let x = ["a": 42];
            x = 3.14;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("Bool is not assignable to map")
    {
        constexpr auto source = R"(func f() {
            let x = ["a": 42];
            x = true;
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("String is not assignable to map")
    {
        constexpr auto source = R"(func f() {
            let x = ["a": 42];
            x = "foo";
        })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("'operator+' cannot be applied to arrays")
    {
        constexpr auto source = R"(func f() { [42] + [3]; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("'operator+' cannot be applied to maps")
    {
        constexpr auto source = R"(func f() { ["a":42] + ["b":3]; })";
        REQUIRE(!typeCheck(diag, source, astContext, context));
    }
    SECTION("'operator==' can be applied to arrays")
    {
        constexpr auto source = R"(func f() { [42] == [3]; })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("'operator==' can be applied to maps")
    {
        constexpr auto source = R"(func f() { ["a":42] == ["b":3]; })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("'operator!=' can be applied to arrays")
    {
        constexpr auto source = R"(func f() { [42] != [3]; })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("'operator!=' can be applied to maps")
    {
        constexpr auto source = R"(func f() { ["a":42] != ["b":3]; })";
        REQUIRE(typeCheck(diag, source, astContext, context));
    }
    SECTION("type resolver can infer type of array indices")
    {
        constexpr auto source = R"(func g(x) { return x; }
        func f() {
            let a = ["b", "c"];
            let b = a[0];
            let c = a[g(1)];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Array<String>"));
        REQUIRE(requireType(context, "b", "String"));
        REQUIRE(requireType(context, "c", "String"));
    }
    SECTION("type resolver can infer type of map keys")
    {
        constexpr auto source = R"(func g(x) { return x; }
        func f() {
            let a = ["b": 42, "c": 43];
            let b = a["b"];
            let c = a[g("c")];
        })";
        REQUIRE(typeCheck(diag, source, astContext, context));
        REQUIRE(requireType(context, "a", "Map<String, Int>"));
        REQUIRE(requireType(context, "b", "Int"));
        REQUIRE(requireType(context, "c", "Int"));
    }
}
