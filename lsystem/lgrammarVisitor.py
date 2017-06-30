# Generated from lsystem.g4 by ANTLR 4.6
from lgrammar.antlr4 import *
from lgrammar.lsystemParser import lsystemParser

from literal_semantic

# This class defines a complete generic visitor for a parse tree produced by lsystemParser.
# ctx.accept(self) visits the ctx

class lgrammarVisitor(ParseTreeVisitor):

    def _get_non_terminal(self, name):
        if name in self.non_terminals:
            return self.non_terminals[name]
        else:
            self.non_terminals[name] = literal_semantic.NonTerminal()
            return self.non_terminals[name]

    # Visit a parse tree produced by lsystemParser#terminal.
    def visitTerminal(self, ctx:lsystemParser.TerminalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#init_sec.
    def visitInit_sec(self, ctx:lsystemParser.Init_secContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#init_start.
    def visitInit_start(self, ctx:lsystemParser.Init_startContext):
        self.start_terminal = self._get_non_terminal(ctx.NT.getText())
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
        self.non_terminals = dict()
        self.start_terminal = None
        return self.visitChildren(ctx)



del lsystemParser
