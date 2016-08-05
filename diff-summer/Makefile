NORI = ../nori/bin/nori
PRODUCTNAME = diff-summer

HEADERS = \
	../somera/*.h \
	../typo-poi/source/thirdparty/*.h \
	../typo-poi/source/*.h \
	*.h

SOURCES = \
	../somera/*.cpp \
	../typo-poi/source/thirdparty/ConvertUTF.c \
	../typo-poi/source/ConsoleColor.cpp \
	../typo-poi/source/EditDistance.cpp \
	../typo-poi/source/UTF8.cpp \
	../typo-poi/source/WordDiff.cpp \
	../typo-poi/source/WordSegmenter.cpp \
	main.cpp

xcode:
	$(NORI) \
		-generator=xcode \
		-o $(PRODUCTNAME) \
		-std=c++14 \
		-stdlib=libc++ \
		-I.. \
		-I../typo-poi/source \
		$(HEADERS) \
		$(SOURCES)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)

rebuild-xcode:
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)
