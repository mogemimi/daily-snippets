NORI = ../nori/bin/nori
PRODUCTNAME = maika

HEADERS = \
	*.h

SOURCES = \
	ASTVisitor.cpp \
	Decl.cpp \
	Entity.cpp \
	Expr.cpp \
	IdentifierResolver.cpp \
	MyLexer.cpp \
	MyDriver.cpp \
	MyParser.cpp \
	Scope.cpp \
	Stmt.cpp \
	TypeResolver.cpp \
	main.cpp

COMPILER_OPTIONS = \
	-o $(PRODUCTNAME) \
	-std=c++17 \
	-stdlib=libc++ \
	-I.. \
	$(SOURCES)

bison:
	@flex -o MyLexer.cpp MyLexer.l
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
