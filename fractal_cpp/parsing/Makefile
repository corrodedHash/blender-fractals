#ANTLR_EXE=/usr/share/java/antlr-complete.jar
ANTLR_EXE=antlr-complete.jar
EXE_CALL=java -jar $(ANTLR_EXE)

TOKEN_TARGETS=lsystem.tokens lsystemLexer.tokens
CPP_TARGETS=lsystemParser.cpp lsystemLexer.cpp lsystemVisitor.cpp lsystemBaseVisitor.cpp
H_TARGETS=lsystemParser.h lsystemLexer.h lsystemVisitor.h lsystemBaseVisitor.h

TARGETS=$(TOKEN_TARGETS) $(CPP_TARGETS) $(H_TARGETS)

OBJECTS=$(patsubst %.cpp,%.o, $(CPP_TARGETS))

CXXFLAGS=-Iantlr-runtime/runtime/src/ -fPIC

all: parser.a antlr4.a

antlr4.a: antlr-runtime/dist/libantlr4-runtime.a
	ln -s $^ $@

parser.a: $(TARGETS) $(OBJECTS) 
	echo $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(OBJECTS): 

antlr-runtime/dist/libantlr4-runtime.a: antlr-runtime/build
	cd antlr-runtime/build && \
	make antlr4_static

antlr-runtime/build:
	mkdir antlr-runtime/build && \
	cd antlr-runtime/build && \
	cmake -DCMAKE_CXX_FLAGS='-fPIC' .. 


$(TARGETS): lsystem.g4
	$(EXE_CALL) -Dlanguage=Cpp -visitor -no-listener lsystem.g4

clean:
	rm -f $(TARGETS)
