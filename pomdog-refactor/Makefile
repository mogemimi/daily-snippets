NORI = ../nori/bin/nori
PRODUCTNAME = pomdog-refactor
HEADERS = \
	../somera/*.h \
	*.h
SOURCES = \
	../somera/*.cpp \
	main.cpp

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
