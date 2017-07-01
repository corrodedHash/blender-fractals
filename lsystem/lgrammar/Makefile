ANTLR_EXE=/usr/share/java/antlr-complete.jar
EXE_CALL=java -jar $(ANTLR_EXE)
java: 
	$(EXE_CALL) lsystem.g4
	javac -cp '$(ANTLR_EXE):$$CLASSPATH' lsystem*.java

python:
	$(EXE_CALL) -Dlanguage=Python3 -visitor lsystem.g4

test:
	cat testfile.txt | grun lsystem code -gui
clean:
	rm lsystemParser.py lsystemLexer.py lsystemListener.py lsystem.tokens lsystemLexer.tokens 
	rm *.java *.class
