NORI = ../nori/bin/nori
PRODUCTNAME = maika

HEADERS = \
	AST/*.h \
	Basic/*.h \
	Driver/*.h \
	CodeGen/*.h \
	Parser/*.h \
	Printer/*.h \
	Sema/*.h \
	*.h

SOURCES = \
	AST/ASTContext.cpp \
	AST/ASTDumper.cpp \
	AST/ASTVisitor.cpp \
	AST/Comment.cpp \
	AST/Decl.cpp \
	AST/Expr.cpp \
	AST/Stmt.cpp \
	AST/Type.cpp \
	Basic/Diagnostic.cpp \
	Basic/Location.cpp \
	Driver/Driver.cpp \
	CodeGen/BytecodeGenerator.cpp \
	CodeGen/Instruction.cpp \
	CodeGen/Runtime.cpp \
	CodeGen/Transpiler.cpp \
	Parser/Lexer.cpp \
	Parser/Parser.cpp \
	Printer/ASTFormatter.cpp \
	Printer/PrettyPrinter.cpp \
	Sema/ASTEvaluator.cpp \
	Sema/Entity.cpp \
	Sema/IdentifierResolver.cpp \
	Sema/Scope.cpp \
	Sema/SemaChecker.cpp \
	Sema/TypeInferer.cpp \
	Sema/TypeResolver.cpp \
	Sema/Value.cpp \
	thirdparty/duktape/duktape.c \
	tests/DumpTest.cpp \
	tests/IdentifierResolverTest.cpp \
	tests/LexerTest.cpp \
	tests/ParserTest.cpp \
	tests/PrettyPrinterTest.cpp \
	tests/SemaCheckerTest.cpp \
	tests/TypeResolverTest.cpp \
	tests/main.cpp

COMPILER_OPTIONS = \
	-o $(PRODUCTNAME) \
	-std=c++17 \
	-stdlib=libc++ \
	-I. \
	-Ithirdparty/catch2 \
	-Ithirdparty \
	$(SOURCES)

format:
	@clang-format -i \
		AST/*.cpp \
		AST/*.h \
		Basic/*.cpp \
		Basic/*.h \
		Driver/*.cpp \
		Driver/*.h \
		CodeGen/*.cpp \
		CodeGen/*.h \
		Printer/*.cpp \
		Printer/*.h \
		Sema/*.cpp \
		Sema/*.h \
		tests/*.cpp

bison:
	@flex Parser/Lexer.l
	@bison Parser/Parser.yy

xcode:
	@flex Parser/Lexer.l
	@bison Parser/Parser.yy
	$(NORI) \
		-generator=xcode \
		$(HEADERS) \
		$(COMPILER_OPTIONS)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)

clean:
	@rm -f Parser/Lexer.cpp
	@rm -f Parser/Lexer.h
	@rm -f Parser/Parser.cpp
	@rm -f Parser/Parser.h
	@rm -f Parser/location.hh
	@rm -f Parser/position.hh
	@rm -f Parser/stack.hh
