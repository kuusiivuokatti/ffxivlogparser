CXX=g++
CXXFLAG=-Wall -Wcast-align
INCLUDE=
OBJDIR=./src/
OBJ=$(OBJDIR)*.cpp
EXECDIR=./lib/
EXECUTABLE=$(EXECDIR)ffxivlogparser.o

all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJ)
	mkdir -p $(EXECDIR)
	$(CXX) $(CXXFLAG) $(INCLUDE) $(OBJ) -o $@

clean:
	rm -rf $(EXECDIR)
