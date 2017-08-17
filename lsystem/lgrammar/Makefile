#ANTLR_EXE=/usr/share/java/antlr-complete.jar
ANTLR_EXE=antlr-complete.jar
EXE_CALL=java -jar $(ANTLR_EXE)

PYTHON_TARGETS=lsystemParser.py lsystemLexer.py lsystemListener.py lsystemVisitor.py
TOKEN_TARGETS=lsystem.tokens lsystemLexer.tokens
CPP_TARGETS=lsystemParser.cpp lsystemLexer.cpp lsystemListener.cpp lsystemVisitor.cpp lsystemBaseListener.cpp lsystemBaseVisitor.cpp
H_TARGETS=lsystemParser.h lsystemLexer.h lsystemListener.h lsystemVisitor.h lsystemBaseListener.h lsystemBaseVisitor.h
JAVA_TARGETS=*.java *.class

TARGETS=$(PYTHON_TARGETS) $(TOKEN_TARGETS) $(CPP_TARGETS) $(H_TARGETS) $(JAVA_TARGETS)


python:
	$(EXE_CALL) -Dlanguage=Python3 -no-visitor -no-listener lsystem.g4

python-dev:
	$(EXE_CALL) -Dlanguage=Python3 -visitor -no-listener lsystem.g4

cpp-dev:
	$(EXE_CALL) -Dlanguage=Cpp -visitor -no-listener lsystem.g4

java:
	$(EXE_CALL) lsystem.g4
	javac -cp '$(ANTLR_EXE):$$CLASSPATH' lsystem*.java


test: java
	cat ../../examples/sierpinski.txt | java -cp .:$(ANTLR_EXE) org.antlr.v4.gui.TestRig lsystem code -gui

clean:
	rm -f $(TARGETS)
