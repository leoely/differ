# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++23

# Opitimzation flags
OPTIMIZATIONFLAGS = -Ofast

# Test flags
TESTFLAGS = -lpthread

# Indluding header files
INCLUDE = -I ./include

# Target executable
TARGET = main

# Test executable
TRIAL = test

# For deleting the target
TARGET_DEL = main.exe

# Software name
NAME = differ

# Source files
SRCS = Parser/Parser.cpp Parser/LocationParser.cpp Parser/DifferParser.cpp command/generate.cpp command/help.cpp main.cpp

# Test direcotry
TESTS = Parser/LocationParserTest.cpp Parser/DifferParserTest.cpp util/serializeStringListMap.cpp

# Library diectory
LIBS = ./lib

# Source directory
SOURCES = ./src

# Test directory
CHECKOUTS = ./test

# Build directory
BUILDS = ./build

# Install directory
INSTALLS = /usr/local/bin

# Object files
OBJS = $(SRCS:%.cpp=$(BUILDS)/application/%.o)

# Test object files
ITEMS = $(TESTS:%.cpp=$(BUILDS)/test/%.o)

# Phony command list
.PHONY: all run clean prepare install uninstall

# Default rule to build and run the executable
all: $(BUILDS)/application/$(TARGET) run

# Rule to link object files into the target executable
$(BUILDS)/application/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPTIMIZATIONFLAGS) -o $(BUILDS)/application/$(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
$(BUILDS)/application/%.o: $(SOURCES)/%.cpp
	$(CXX) $(CXXFLAGS) $(OPTIMIZATIONFLAGS) $(INCLUDE) -c $< -o $@

# Rule to run the executable
run: prepare $(BUILDS)/application/$(TARGET)
	$(BUILDS)/application/$(TARGET)

# Rule to prepare the build directory
prepare:
	@mkdir -p $(BUILDS)/application/Parser
	@mkdir -p $(BUILDS)/application/command
	@mkdir -p $(BUILDS)/test/Parser
	@mkdir -p $(BUILDS)/test/util

# Rule to remove generated files
clean:
	-@rm -rvf $(BUILDS)/*

# Rule to installing the software
install: $(BUILDS)/application/$(TARGET)
	@cp $(BUILDS)/application/$(TARGET) $(INSTALLS)/$(NAME)

# Rule to uninstall software
uninstall:
	-@rm -rvf $(INSTALLS)/$(NAME)

# Rule to running unit test
test: prepare $(BUILDS)/test/$(TRIAL)
	$(BUILDS)/test/$(TRIAL)

# Rule to link object files into the test executable
$(BUILDS)/test/$(TRIAL): $(ITEMS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(TESTFLAGS) $(INCLUDE) -o $(BUILDS)/test/$(TRIAL) $(ITEMS) $(LIBS)/libgtest.a $(LIBS)/libgtest_main.a $(BUILDS)/application/Parser/LocationParser.o $(BUILDS)/application/Parser/Parser.o $(BUILDS)/application/Parser/DifferParser.o

# Rule to compile .cpp files into .o files
$(BUILDS)/test/%.o: $(CHECKOUTS)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
