NORI = ../nori/bin/nori
PRODUCTNAME = matoi

HEADERS = \
	../somera/*.h \
	thirdparty/*.h

SOURCES = \
	../somera/*.cpp \
	thirdparty/*.c \
	main.cpp

COMPILER_OPTIONS = \
	-o $(PRODUCTNAME) \
	-std=c++14 \
	-stdlib=libc++ \
	-I.. \
	$(SOURCES)

xcode:
	$(NORI) \
		-generator=xcode \
		$(HEADERS) \
		$(COMPILER_OPTIONS)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)
