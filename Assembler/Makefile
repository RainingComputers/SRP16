.PHONY : help clean all build
help :
	@echo "clean"
	@echo "      Remove auto-generated files."
	@echo "build"
	@echo "      Build release executable."
	@echo "build DEBUG=1"
	@echo "      Build executable for debugging"

# Name of the executable
EXEC_NAME = srp16asm

# C++ compiler
CXX ?= g++

# Set C++ compiler flags and build type
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CXXFLAGS = -g
	BUILD_TYPE = debug
else
    CXXFLAGS = -O3
	BUILD_TYPE = release
endif

# Find all .cpp files in src/
SOURCES = $(shell find src/ -name '*.cpp')
# Set object file names, all object files are in obj/
OBJECTS = $(SOURCES:src/%.cpp=obj/$(BUILD_TYPE)/%.o)

# Remove object files and executable
clean:
	rm -f -r bin/
	rm -f -r obj/

# For compiling .cpp files in src/ to .o object files in obj/
obj/$(BUILD_TYPE)/%.o: src/%.cpp
	mkdir -p obj/$(BUILD_TYPE)/
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking all object files to executable 
bin/$(BUILD_TYPE)/$(EXEC_NAME): $(OBJECTS)
	mkdir -p bin/$(BUILD_TYPE)/
	$(CXX) $(CXXFLAGS) -o bin/$(BUILD_TYPE)/$(EXEC_NAME) $(OBJECTS)

all: bin/$(BUILD_TYPE)/$(EXEC_NAME)

# Build executable
build: all