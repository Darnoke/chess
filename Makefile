# Makefile

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./libchess/src
LDFLAGS = -L./build/static -lchess

# Target executable name
TARGET = easyChess

# Source files
SOURCES = main.cpp ChessEngine.cpp Evaluator.cpp
# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# To obtain object files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
