all: 
	antlr4 lsystem.g4
	javac -cp '/usr/share/java/antlr-complete.jar:$$CLASSPATH' lsystem*.java

test:
	cat testfile.txt | grun lsystem code -tree

