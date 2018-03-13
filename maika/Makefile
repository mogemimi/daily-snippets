NORI = ../nori/bin/nori
PRODUCTNAME = maika

HEADERS = \
	*.h

SOURCES = \
	AST/Decl.cpp \
	AST/Expr.cpp \
	AST/Stmt.cpp \
	AST/Type.cpp \
	Sema/Entity.cpp \
	Sema/Scope.cpp \
	ASTContext.cpp \
	ASTDumper.cpp \
	ASTVisitor.cpp \
	Diagnostic.cpp \
	Formatter.cpp \
	IdentifierResolver.cpp \
	MyLexer.cpp \
	MyDriver.cpp \
	MyParser.cpp \
	TypeInferer.cpp \
	TypeResolver.cpp \
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
		AST/Decl.cpp \
		AST/Decl.h \
		AST/Expr.cpp \
		AST/Expr.h \
		AST/Stmt.cpp \
		AST/Stmt.h \
		AST/Type.cpp \
		AST/Type.h \
		Sema/Entity.cpp \
		Sema/Entity.h \
		Sema/Scope.cpp \
		Sema/Scope.h \
		ASTContext.cpp \
		ASTContext.h \
		ASTDumper.cpp \
		ASTDumper.h \
		ASTVisitor.cpp \
		ASTVisitor.h \
		Diagnostic.cpp \
		Diagnostic.h \
		Formatter.cpp \
		Formatter.h \
		Forward.h \
		IdentifierResolver.cpp \
		IdentifierResolver.h \
		MyDriver.cpp \
		MyDriver.h \
		TypeInferer.cpp \
		TypeInferer.h \
		TypeResolver.cpp \
		TypeResolver.h \
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
