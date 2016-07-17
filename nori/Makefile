CXX = clang++
PRODUCTNAME = nori

HEADERS = \
	../somera/*.h \
	*.h

SOURCES = \
	../somera/*.cpp \
	MSBuild.cpp \
	XcodeProject.cpp \
	main.cpp

COMPILER_OPTIONS = \
	-o $(PRODUCTNAME) \
	-std=c++14 \
	-stdlib=libc++ \
	-I.. \
	$(SOURCES)

bootstrap:
	$(CXX) $(COMPILER_OPTIONS)
	@mkdir -p bin
	@mv nori bin/

xcode:
	./bin/nori \
		-generator=xcode \
		$(HEADERS) \
		$(COMPILER_OPTIONS)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)
