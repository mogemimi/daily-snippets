NORI = ../nori/bin/nori
PRODUCTNAME = maika

HEADERS = \
	*.h

SOURCES = \
	ASTContext.cpp \
	ASTDumper.cpp \
	ASTVisitor.cpp \
	Decl.cpp \
	Diagnostic.cpp \
	Entity.cpp \
	Expr.cpp \
	Formatter.cpp \
	IdentifierResolver.cpp \
	MyLexer.cpp \
	MyDriver.cpp \
	MyParser.cpp \
	Scope.cpp \
	Stmt.cpp \
	Type.cpp \
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
		ASTContext.cpp \
		ASTContext.h \
		ASTDumper.h \
		ASTDumper.cpp \
		ASTDumper.h \
		ASTVisitor.cpp \
		ASTVisitor.h \
		Decl.cpp \
		Decl.h \
		Diagnostic.cpp \
		Diagnostic.h \
		Entity.cpp \
		Entity.h \
		Expr.cpp \
		Expr.h \
		Expr.cpp \
		Expr.h \
		Formatter.cpp \
		Formatter.h \
		Forward.h \
		IdentifierResolver.cpp \
		IdentifierResolver.h \
		MyDriver.cpp \
		MyDriver.h \
		Scope.cpp \
		Scope.h \
		Stmt.cpp \
		Stmt.h \
		Type.cpp \
		Type.h \
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
