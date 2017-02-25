CXX = clang++
NORI = ../nori/bin/nori
PRODUCT_NAME = aligndiff

CXXFLAGS = \
	-std=c++14 \
	-stdlib=libc++ \
	-O2 \
	-Wall \
	-I.
HEADERS = \
	*.h
SOURCES = \
	algorithms/editdistance_dp.cpp \
	algorithms/editdistance_linearspace.cpp \
	algorithms/editdistance_ondgreedy.cpp \
	algorithms/lcslength_dp.cpp \
	algorithms/lcslength_linearspace.cpp \
	algorithms/lcslength_ondgreedy.cpp \
	algorithms/ses_dp.cpp \
	algorithms/ses_linearspace.cpp \
	algorithms/ses_ondgreedy.cpp \
	algorithms/ses_weavinglinearspace.cpp \
	aligndiff.cpp \
	utility.cpp \
	main.cpp

build:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(PRODUCT_NAME) $(SOURCES) $(LDLIBS)

xcode:
	$(NORI) \
		-generator=xcode \
		-o $(PRODUCT_NAME) \
		$(CXXFLAGS) \
		$(LDFLAGS) \
		$(HEADERS) \
		$(SOURCES) \
		$(LDLIBS)
	@xcodebuild -project $(PRODUCT_NAME).xcodeproj -configuration Release
	@mkdir -p bin
	@cp build/Release/$(PRODUCT_NAME) bin/$(PRODUCT_NAME)
