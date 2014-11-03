default: ../sat ../edt

test: ../run-test
	(cd ..; ./run-test)

parser: parser.tab.cpp parser.tab.hpp lex.yy.cpp

SUFFIXES += .d
SRC := $(sort $(wildcard *.cpp) parser.tab.cpp lex.yy.cpp)
MAINS := main.o main-test.o main-edt.o
ALLOBJECTS := $(SRC:%.cpp=%.o)
OBJECTS := $(filter-out $(MAINS),$(ALLOBJECTS))
TEST_LDDEPS := $(LDDEPS) -L../unittest-cpp -lUnitTest++
CXXFLAGS := -Wall -Wextra -std=c++0x -I../unittest-cpp/src

UNITTEST := ../unittest-cpp/libUnitTest++.a
$(UNITTEST):
	make -C ../unittest-cpp

clean:
	rm -f *.d *.o 
	rm -f *~ 
	rm -f ../sat ../run-test ../edt

cleanparser:
	rm -f parser.tab.cpp lex.yy.cpp

help:
	sed -n -e 's/^#HELP\(.*\)$$/\1/p' < Makefile

#HELP
#HELP pour afficher l'aide du Makefile
#HELP make help
#HELP
#HELP pour compiler le projet
#HELP make 
#HELP
#HELP pour lancer les tests
#HELP make test
#HELP
#HELP pour nettoyer les fichiers compilés et temporaires
#HELP make clean
#HELP

../sat: $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) main.o $(LDDEPS) -o ../sat

../run-test: $(OBJECTS) main-test.o $(UNITTEST)
	$(CXX) $(CXXFLAGS) $(OBJECTS) main-test.o $(TEST_LDDEPS) -o ../run-test

../edt: $(OBJECTS) main-edt.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) main-edt.o $(LDDEPS) -o ../edt

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM $*.cpp -MF $*.d

ifeq ($(findstring parser,$(MAKECMDGOALS)),parser)
parser.tab.cpp parser.tab.hpp: parser.y
	bison -d parser.y --output-file=parser.tab.cpp

lex.yy.cpp: parser.lex
	flex -o lex.yy.cpp parser.lex 
endif

ifneq ($(subst parser,,$(MAKECMDGOALS)),clean) 
include $(ALLOBJECTS:%.o=%.d)
endif

.PHONY: default test parser

