#  Makefile 
#  Auteur : OUKHEMANOU Mohand

CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = kmeans

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(TARGET) $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
