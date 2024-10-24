CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -lm
SRCS = src/main.cpp src/quick_select.cpp src/lazy_select.cpp src/sorting.cpp src/benchmark.cpp
OBJS = $(SRCS:src/%.cpp=build/%.o)

# Output executable
TARGET = benchmark

# Rule to create the target
all: $(TARGET)
	./$(TARGET) # Run the executable after building
# Linking the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files in build/
build/%.o: src/%.cpp
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the object files and executable
clean:
	rm -rf build $(TARGET)
