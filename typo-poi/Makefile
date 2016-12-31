NORI = ../nori/bin/nori
PRODUCTNAME = typo-poi

HEADERS = \
	../somera/*.h \
	source/thirdparty/*.h \
	source/*.h

SOURCES = \
	../somera/*.cpp \
	source/thirdparty/ConvertUTF.c \
	source/ConsoleColor.cpp \
	source/EditDistance.cpp \
	source/SpellChecker.cpp \
	source/Typo.cpp \
	source/UTF8.cpp \
	source/WordDiff.cpp \
	source/WordSegmenter.cpp \
	source/main.cpp

ifeq ($(OS),Windows_NT)
	SOURCES += source/SpellCheckWin.cpp
endif
ifeq ($(shell uname -s),Darwin)
	SOURCES += source/SpellCheckMac.mm
endif

xcode:
	$(NORI) \
		-generator=xcode \
		-o $(PRODUCTNAME) \
		-std=c++14 \
		-stdlib=libc++ \
		-lAppKit.framework \
		-I.. \
		$(HEADERS) \
		$(SOURCES)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)

developer-xcode:
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)
