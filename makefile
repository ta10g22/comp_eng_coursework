# ------------------------------------------------------------
#  Makefile for MIPS-like pipeline simulator
# ------------------------------------------------------------

CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2     # C++11 + good warnings
LDFLAGS  := $(CXXFLAGS)

OBJS := main.o alu.o controlunit.o datamemory.o \
        hazardunit.o instructionmemory.o parser.o \
        programcounter.o registerfile.o

# Default target ------------------------------------------------
simulation: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o simulation

# Pattern rule for every .cpp → .o --------------------------------
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# main.cpp doesn’t have a matching .h, so list it separately
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean ----------------------------------------------------------
clean:
	rm -f $(OBJS) simulation

.PHONY: clean