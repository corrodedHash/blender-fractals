from .lsystem import Lsystem
from .lgrammarVisitor import lgrammarVisitor
from .lgrammar import lsystemLexer, lsystemParser, antlr4 

def parse(text):
    my_lexer = lsystemLexer.lsystemLexer(antlr4.InputStream(text))
    my_parser = lsystemParser.lsystemParser(antlr4.CommonTokenStream(my_lexer))
    return lgrammarVisitor().visit(my_parser.code())

