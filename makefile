BISON = bison
BISONFLAGS = 
FLEX = flex
CXX = g++
CXXFLAGS = -I./include -g

SRCDIR = ./src/
SRC = $(addprefix $(SRCDIR), parser.cpp scanner.cpp) $(wildcard $(SRCDIR)*.cpp)

OBJDIR = ./obj/
OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:cpp=o)))

BIN = brainfuck

all: $(BIN)

$(SRCDIR)%.cpp %.hpp: $(SRCDIR)%.yy
	$(BISON) $(BISONFLAGS) -o $(SRCDIR)$*.cpp $<
	mv $(SRCDIR)$*.hpp ./include/$*.hpp

$(SRCDIR)%.cpp: $(SRCDIR)%.ll
	$(FLEX) $(FLEXFLAGS) -o $@ $<

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CXX) -o $@ $^

$(BIN).o: parser.hpp
brainfuckmem.o: brainfuckmem.hpp
parser.o: parser.hpp
scanner.o: parser.hpp

clean:
	rm -f $(BIN) $(SRCDIR)parser.cpp $(SRCDIR)scanner.cpp
	rm -f ./include/parser.hpp
	rm -rf $(OBJDIR)