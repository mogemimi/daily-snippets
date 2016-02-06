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

bootstrap:
	$(CXX) \
		-o $(PRODUCTNAME) \
		-std=c++14 \
		-stdlib=libc++ \
		-I.. \
		$(SOURCES)
	@mkdir -p bin
	@mv nori bin/

xcode:
	./bin/nori \
		-generator=xcode \
		-o $(PRODUCTNAME) \
		-std=c++14 \
		-stdlib=libc++ \
		-I.. \
		$(HEADERS) \
		$(SOURCES)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)
