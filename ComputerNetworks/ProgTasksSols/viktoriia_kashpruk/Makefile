CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = traceroute

SRCS = icmp_utils.cpp icmp_send.cpp traceroute.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
