BISON = bison
CXX = g++
FLEX = flex

OBJDIR = ./obj/
OBJ = $(addprefix $(OBJDIR), parser.o scanner.o brainfuckmem.o driver.o $(BIN).o)

BIN = brainfuck

all: $(BIN)

%.cpp %.hpp: %.yy
	$(BISON) $(BISONFLAGS) -o $*.cpp $<

%.cpp: %.ll
	$(FLEX) $(FLEXFLAGS) -o $@ $<

$(OBJDIR)%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CXX) -o $@ $^

$(BIN).o: parser.hpp
brainfuckmem.o: brainfuckmem.hpp
parser.o: parser.hpp
scanner.o: parser.hpp

clean:
	rm -f $(BIN) parser.hpp parser.cpp scanner.cpp
	rm -rf $(OBJDIR)