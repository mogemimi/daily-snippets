NORI = ../nori/bin/nori
PRODUCTNAME = mami
HEADERS = \
	../somera/*.h \
	../somera/signals/*.h \
	*.h
SOURCES = \
	../somera/*.cpp \
	../somera/signals/*.cpp \
	example/EchoServer/main.cpp \
	*.cpp

xcode:
	$(NORI) \
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
