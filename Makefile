CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET = myprogram

all: $(TARGET)
	./$(TARGET)  # Run the application after building

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)