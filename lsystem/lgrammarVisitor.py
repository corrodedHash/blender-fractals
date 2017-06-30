# Generated from lsystem.g4 by ANTLR 4.6
from lgrammar.antlr4 import *
from lgrammar.lsystemParser import lsystemParser

from literal_semantic

# This class defines a complete generic visitor for a parse tree produced by lsystemParser.
# ctx.accept(self) visits the ctx

class lgrammarVisitor(ParseTreeVisitor):

    def aggregateResult(self, aggregate, nextResult):
        if aggregate is None:
            if nextResult is None:
                return None
            return [nextResult]
        aggregate.append(nextResult)
        return aggregate

    def visitTerminal(self, ctx):
        if ctx.type == lsystemParser.NT:
            return self.lsystem.get_non_terminal(ctx.getText)
        else:
            return None

    # Visit a parse tree produced by lsystemParser#terminal.
    def visitTerm(self, ctx:lsystemParser.TermContext):
        if ctx.ROT() is not None:
            return literal_semantic.RotateTerminal(float(ctx.FLOAT()))
        elif ctx.MOVE() is not None:
            return literal_semantic.MoveTerminal(float(ctx.FLOAT()))
        elif ctx.PUSH() is not None:
            return literal_semantic.PushTerminal()
        elif ctx.POP() is not None:
            return literal_semantic.PopTerminal()

        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#init_sec.
    def visitInit_sec(self, ctx:lsystemParser.Init_secContext):
        ctx.init_start.accept()


    # Visit a parse tree produced by lsystemParser#init_start.
    def visitInit_start(self, ctx:lsystemParser.Init_startContext):
        self.lsystem.start = self.lsystem.get_non_terminal(ctx.NT.getText())

    # Visit a parse tree produced by lsystemParser#rule_sec.
    def visitRule_sec(self, ctx:lsystemParser.Rule_secContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#rule_entity.
    def visitRule_entity(self, ctx:lsystemParser.Rule_entityContext):
        self.lsystem.get_non_terminal(ctx.NT().getText()).transition = ctx.rule_res().accept(self)


    # Visit a parse tree produced by lsystemParser#rule_res.
    def visitRule_res(self, ctx:lsystemParser.Rule_resContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#final_sec.
    def visitFinal_sec(self, ctx:lsystemParser.Final_secContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#final_rule_entity.
    def visitFinal_rule_entity(self, ctx:lsystemParser.Final_rule_entityContext):
        self.lsystem.get_non_terminal(ctx.NT().getText()).final_transition = ctx.rule_res().accept(self)


    # Visit a parse tree produced by lsystemParser#final_rule_res.
    def visitFinal_rule_res(self, ctx:lsystemParser.Final_rule_resContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by lsystemParser#code.
    def visitCode(self, ctx:lsystemParser.CodeContext):
        self.lsystem = Lsystem()
        self.visitChildren(ctx)
        return self.lsystem

del lsystemParser
