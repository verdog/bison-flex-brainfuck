# This Makefile is designed to be simple and readable.  It does not
# aim at portability.  It requires GNU Make.

BISON = bison
CXX = g++
FLEX = flex
BIN = brainfuck

all: $(BIN)

%.cpp %.hpp: %.yy
	$(BISON) $(BISONFLAGS) -o $*.cpp $<

%.cpp: %.ll
	$(FLEX) $(FLEXFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(BIN).o driver.o parser.o scanner.o
	$(CXX) -o $@ $^

$(BIN).o: parser.hpp
parser.o: parser.hpp
scanner.o: parser.hpp

clean:
	rm -f $(BIN) *.o parser.hpp parser.cpp scanner.cpp
