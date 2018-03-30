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
	Parser/MyLexer.cpp \
	Parser/MyParser.cpp \
	Printer/Formatter.cpp \
	Sema/Entity.cpp \
	Sema/IdentifierResolver.cpp \
	Sema/Scope.cpp \
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
		AST/ASTContext.cpp \
		AST/ASTContext.h \
		AST/ASTDumper.cpp \
		AST/ASTDumper.h \
		AST/ASTVisitor.cpp \
		AST/ASTVisitor.h \
		AST/Comment.cpp \
		AST/Comment.h \
		AST/Decl.cpp \
		AST/Decl.h \
		AST/Expr.cpp \
		AST/Expr.h \
		AST/Stmt.cpp \
		AST/Stmt.h \
		AST/Type.cpp \
		AST/Type.h \
		Basic/Diagnostic.cpp \
		Basic/Diagnostic.h \
		Basic/Location.cpp \
		Basic/Location.h \
		Basic/Forward.h \
		Driver/Driver.cpp \
		Driver/Driver.h \
		CodeGen/BytecodeGenerator.cpp \
		CodeGen/BytecodeGenerator.h \
		CodeGen/Instruction.cpp \
		CodeGen/Instruction.h \
		CodeGen/Opcode.h \
		Printer/Formatter.cpp \
		Printer/Formatter.h \
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
		tests/DumpTest.cpp \
		tests/LexerTest.cpp \
		tests/main.cpp

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
