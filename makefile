# This Makefile is designed to be simple and readable.  It does not
# aim at portability.  It requires GNU Make.

BISON = bison
CXX = g++
FLEX = flex
BIN = brainfuck

all: $(BIN)

%.cc %.hh: %.yy
	$(BISON) $(BISONFLAGS) -o $*.cc $<

%.cc: %.ll
	$(FLEX) $(FLEXFLAGS) -o $@ $<

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(BIN).o driver.o parser.o scanner.o
	$(CXX) -o $@ $^

$(BIN).o: parser.hh
parser.o: parser.hh
scanner.o: parser.hh

clean:
	rm -f $(BIN) *.o parser.hh parser.cc scanner.cc
