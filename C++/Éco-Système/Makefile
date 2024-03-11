#  Makefile 
#  Auteur : OUKHEMANOU Mohand

CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -g
SRCDIR = src
BUILDDIR = build
TARGET = eco_systeme

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(TARGET) $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -c -o $@ $<

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean


