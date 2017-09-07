LIBS=parsing/parser.a parsing/antlr4.a

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
CXXFLAGS=-std=c++14 -O3 -Iparsing/antlr-runtime/runtime/src/ 
CXX=clang++


all: $(LIBS)
	python setup.py build_ext -i
	

$(LIBS):
	make -C parsing

clean:
	rm -rf fractal.cpp build/
