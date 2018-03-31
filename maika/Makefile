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
	Parser/MyLexer.cpp \
	Parser/MyParser.cpp \
	Printer/Formatter.cpp \
	Sema/Entity.cpp \
	Sema/IdentifierResolver.cpp \
	Sema/Scope.cpp \
	Sema/TypeChecker.cpp \
	Sema/TypeInferer.cpp \
	Sema/TypeResolver.cpp \
	tests/DumpTest.cpp \
	tests/LexerTest.cpp \
	tests/main.cpp

COMPILER_OPTIONS = \
	-o $(PRODUCTNAME) \
	-std=c++17 \
	-stdlib=libc++ \
	-I. \
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
	@flex Parser/MyLexer.l
	@bison Parser/MyParser.yy

xcode:
	@flex Parser/MyLexer.l
	@bison Parser/MyParser.yy
	$(NORI) \
		-generator=xcode \
		$(HEADERS) \
		$(COMPILER_OPTIONS)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)

clean:
	@rm -f Parser/MyLexer.cpp
	@rm -f Parser/MyParser.cpp
	@rm -f Parser/MyParser.h
	@rm -f Parser/location.hh
	@rm -f Parser/position.hh
	@rm -f Parser/stack.hh
