# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

# Source and build directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

# Object files (in the build directory)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
TARGET := bin/program

# Default rule
all: $(TARGET)

# Linking the target executable
$(TARGET): $(OBJS)
	if not exist $(dir $@) mkdir $(dir $@)
	$(CXX) $^ -o $@

# Rule for building object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist $(dir $@) mkdir $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
