NORI = ../nori/bin/nori
PRODUCTNAME = slackbot
HEADERS = \
	../somera/*.h \
	*.h
SOURCES = \
	../somera/*.cpp \
	HttpUtility.cpp \
	HttpService.cpp \
	iTunesNowPlaying.cpp \
	main.cpp \
	SlackClient.cpp \
	TerminalHelper.cpp

xcode:
	$(NORI) \
		-generator=xcode \
		-o $(PRODUCTNAME) \
		-std=c++14 \
		-stdlib=libc++ \
		-llibcurl.tbd \
		-I.. \
		-Irapidjson/include \
		$(HEADERS) \
		$(SOURCES)
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)
