NORI = ../nori/bin/nori
PRODUCTNAME = githubapis

HEADERS = \
	../somera/*.h \
	../slackbot/*.h \
	*.h

SOURCES = \
	../somera/*.cpp \
	../slackbot/HttpUtility.cpp \
	../slackbot/HttpService.cpp \
	../slackbot/TerminalHelper.cpp \
	GitHubClient.cpp \
	main.cpp

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

rebuild-xcode:
	@xcodebuild -project $(PRODUCTNAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCTNAME) bin/$(PRODUCTNAME)
