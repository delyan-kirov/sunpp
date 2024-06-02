# Compiler and linker
CXX = g++

# Compiler and linker flags
CXXFLAGS = -Wall -I/usr/include/raylib
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Target executable
TARGET = main.out

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the application
run: $(TARGET)
	./$(TARGET)
