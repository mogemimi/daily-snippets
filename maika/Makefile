NORI = ../nori/bin/nori
PRODUCTNAME = maika

HEADERS = \
	AST/*.h \
	Basic/*.h \
	Sema/*.h \
	*.h

SOURCES = \
	AST/ASTContext.cpp \
	AST/ASTDumper.cpp \
	AST/ASTVisitor.cpp \
	AST/Decl.cpp \
	AST/Expr.cpp \
	AST/Stmt.cpp \
	AST/Type.cpp \
	Sema/Entity.cpp \
	Sema/IdentifierResolver.cpp \
	Sema/Scope.cpp \
	Sema/TypeInferer.cpp \
	Sema/TypeResolver.cpp \
	Diagnostic.cpp \
	Formatter.cpp \
	MyLexer.cpp \
	MyDriver.cpp \
	MyParser.cpp \
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
		AST/ASTContext.cpp \
		AST/ASTContext.h \
		AST/ASTDumper.cpp \
		AST/ASTDumper.h \
		AST/ASTVisitor.cpp \
		AST/ASTVisitor.h \
		AST/Decl.cpp \
		AST/Decl.h \
		AST/Expr.cpp \
		AST/Expr.h \
		AST/Stmt.cpp \
		AST/Stmt.h \
		AST/Type.cpp \
		AST/Type.h \
		Basic/Forward.h \
		Sema/Entity.cpp \
		Sema/Entity.h \
		Sema/IdentifierResolver.cpp \
		Sema/IdentifierResolver.h \
		Sema/Scope.cpp \
		Sema/Scope.h \
		Sema/TypeInferer.cpp \
		Sema/TypeInferer.h \
		Sema/TypeResolver.cpp \
		Sema/TypeResolver.h \
		Diagnostic.cpp \
		Diagnostic.h \
		Formatter.cpp \
		Formatter.h \
		MyDriver.cpp \
		MyDriver.h \
		tests/DumpTest.cpp \
		tests/LexerTest.cpp \
		tests/main.cpp

bison:
	@flex MyLexer.l
	@bison MyParser.yy

xcode:
	@flex -o MyLexer.cpp MyLexer.l
	@bison MyParser.yy
	$(NORI) \
		-generator=xcode \
		$(HEADERS) \
		$(COMPILER_OPTIONS)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)

clean:
	@rm -f MyLexer.cpp
	@rm -f MyParser.cpp
	@rm -f MyParser.h
	@rm -f location.hh
	@rm -f position.hh
	@rm -f stack.hh
