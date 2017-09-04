LIBS=parsing/parser.a parsing/antlr4.a

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
CXXFLAGS=-std=c++14 -O3 -Iparsing/antlr-runtime/runtime/src/ 
CXX=clang++


a.out: $(OBJECTS)
	clang++ $(OBJECTS) $(LIBS) 

parsing/parser.a parsing/antlr4.a:
	make -C parsing

clean:
	rm $(OBJECTS) .depend

.depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -MM > .depend

include .depend
