CXX=g++
CXXFLAG=-Wall -Wcast-align

#PROD
INCLUDE=
OBJDIR=./src/
OBJ=$(OBJDIR)*.cpp
EXECDIR=./lib/
EXECUTABLE=$(EXECDIR)ffxivlogparser.o

#TEST
TESTINCLUDE=
TESTOBJDIR=./test/
TESTOBJ=$(TESTOBJDIR)*.cpp
TESTEXECDIR=./lib/
TESTEXECUTABLE=$(EXECDIR)test.o

all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJ)
	mkdir -p $(EXECDIR)
	$(CXX) $(CXXFLAG) $(INCLUDE) $(OBJ) -o $@

test: $(TESTEXECUTABLE)
$(TESTEXECUTABLE): $(TESTOBJ)
	mkdir -p $(TESTEXECDIR)
	$(CXX) $(CXXFLAG) $(TESTINCLUDE) $(TESTOBJ) -o $@

clean:
	rm -rf $(EXECDIR)
