java: 
	antlr4 lsystem.g4
	javac -cp '/usr/share/java/antlr-complete.jar:$$CLASSPATH' lsystem*.java

python:
	antlr4 -Dlanguage=Python3 -visitor lsystem.g4

test:
	cat testfile.txt | grun lsystem code -gui
clean:
	rm lsystemParser.py lsystemLexer.py lsystemListener.py lsystem.tokens lsystemLexer.tokens 
	rm *.java *.class
