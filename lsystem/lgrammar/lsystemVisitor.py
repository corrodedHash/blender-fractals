# Generated from lsystem.g4 by ANTLR 4.6
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .lsystemParser import lsystemParser
else:
    from lsystemParser import lsystemParser

# This class defines a complete generic visitor for a parse tree produced by lsystemParser.

class lsystemVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by lsystemParser#terminal.
    def visitTerminal(self, ctx:lsystemParser.TerminalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#init_sec.
    def visitInit_sec(self, ctx:lsystemParser.Init_secContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#init_start.
    def visitInit_start(self, ctx:lsystemParser.Init_startContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#rule_sec.
    def visitRule_sec(self, ctx:lsystemParser.Rule_secContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#rule_entity.
    def visitRule_entity(self, ctx:lsystemParser.Rule_entityContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#rule_res.
    def visitRule_res(self, ctx:lsystemParser.Rule_resContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#final_sec.
    def visitFinal_sec(self, ctx:lsystemParser.Final_secContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#final_rule_entity.
    def visitFinal_rule_entity(self, ctx:lsystemParser.Final_rule_entityContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#final_rule_res.
    def visitFinal_rule_res(self, ctx:lsystemParser.Final_rule_resContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#code.
    def visitCode(self, ctx:lsystemParser.CodeContext):
        return self.visitChildren(ctx)



del lsystemParser