NORI = ../nori/bin/nori
PRODUCTNAME = textcxx

HEADERS = \
    ../somera/*.h \
    thirdparty/ConvertUTF.h

SOURCES = \
    ../somera/*.cpp \
    thirdparty/ConvertUTF.c \
    main.cpp

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
