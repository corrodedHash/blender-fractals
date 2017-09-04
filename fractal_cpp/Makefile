SOURCES=main.o literal.o fractalgen.o #lgrammarVisitor.cpp
HEADER=fractalgen.h lgrammarVisitor.h literal.h
LIBS=-L$$(pwd) -l:parsing/parser.a -l:parsing/antlr4.a
CXXFLAGS=-std=c++14 -Iparsing/antlr-runtime/runtime/src/ 


a.out: $(SOURCES) $(HEADER) parsing/parser.a parsing/antlr4.a
	clang++ $(FLAGS) $(SOURCES) $(LIBS) 

parsing/parser.a parsing/antlr4.a:
	make -C parsing

