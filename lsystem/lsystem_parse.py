from .lgrammar.lsystemLexer import lsystemLexer
from .lgrammar.lsystemParser import lsystemParser
from .lgrammarVisitor import lgrammarVisitor
import antlr4


def parse(text):
    my_lexer = lsystemLexer(antlr4.InputStream(text))
    my_parser = lsystemParser(antlr4.CommonTokenStream(my_lexer))
    return lgrammarVisitor().visit(my_parser.code())
