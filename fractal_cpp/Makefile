LIBS=parsing/parser.a parsing/antlr4.a

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
CXXFLAGS=-std=c++14 -O3 -Iparsing/antlr-runtime/runtime/src/ 
CXX=clang++


all: $(LIBS)
	python setup.py build_ext -i

test: all
	blender --python-expr 'import bpy; bpy.ops.mesh.add_fractal()'
	

$(LIBS):
	make -C parsing

clean:
	rm -rf fractal.cpp build/
