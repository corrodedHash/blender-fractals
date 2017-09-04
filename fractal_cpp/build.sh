#!/bin/bash

FLAGS="-std=c++14 -Iparsing/antlr-runtime/runtime/src/ -L$(pwd)" 
LIBS="-l:parsing/parser.a -l:parsing/antlr4.a"
SOURCES="main.cpp fractalgen.cpp literal.cpp"

clang++ $FLAGS $SOURCES $LIBS 
