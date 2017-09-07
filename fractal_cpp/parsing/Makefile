#ANTLR_EXE=/usr/share/java/antlr-complete.jar
ANTLR_EXE=antlr-complete.jar
EXE_CALL=java -jar $(ANTLR_EXE)
ANTLR_RUNTIME=antlr-runtime

EXE_URL=http://www.antlr.org/download/antlr-4.7-complete.jar
RUNTIME_URL=http://www.antlr.org/download/antlr4-cpp-runtime-4.7-source.zip

TOKEN_TARGETS=lsystem.tokens lsystemLexer.tokens
CPP_TARGETS=lsystemParser.cpp lsystemLexer.cpp lsystemVisitor.cpp lsystemBaseVisitor.cpp
H_TARGETS=lsystemParser.h lsystemLexer.h lsystemVisitor.h lsystemBaseVisitor.h

TARGETS=$(TOKEN_TARGETS) $(CPP_TARGETS) $(H_TARGETS)

OBJECTS=$(patsubst %.cpp,%.o, $(CPP_TARGETS))

CXXFLAGS=-Iantlr-runtime/runtime/src/ -fPIC

all: $(ANTLR_EXE) $(ANTLR_RUNTIME) parser.a antlr4.a

antlr4.a: antlr-runtime/dist/libantlr4-runtime.a
	ln -s $^ $@

parser.a: $(TARGETS) $(OBJECTS) 
	echo $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(ANTLR_RUNTIME)/dist/libantlr4-runtime.a: $(ANTLR_RUNTIME)/build
	cd $(ANTLR_RUNTIME)/build && \
	make antlr4_static

$(ANTLR_RUNTIME)/build:
	mkdir $(ANTLR_RUNTIME)/build && \
	cd $(ANTLR_RUNTIME)/build && \
	cmake -DCMAKE_CXX_FLAGS='-fPIC' .. 

$(ANTLR_EXE):
	curl $(EXE_URL) --output $@ 

$(ANTLR_RUNTIME):
	mkdir $(ANTLR_RUNTIME)
	cd $(ANTLR_RUNTIME) && \
	curl $(RUNTIME_URL) --output antlr-runtime.zip && \
	unzip -q antlr-runtime.zip


$(TARGETS): lsystem.g4
	$(EXE_CALL) -Dlanguage=Cpp -visitor -no-listener lsystem.g4

clean:
	rm -f $(TARGETS) $(OBJECTS) antlr4.a parser.a

ultraclean: clean
	rm -rf $(ANTLR_RUNTIME) $(ANTLR_EXE)

