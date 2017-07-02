# Generated from lsystem.g4 by ANTLR 4.6
import lsystem.lgrammar.lsystemParser as lsp
import lsystem.lgrammar.antlr4 as antlr4

from lsystem.literal_semantic import (RotateTerminal, MoveTerminal,
                                      PushTerminal, PopTerminal)
from lsystem.lsystem_class import Lsystem

# This class defines a complete generic visitor for a parse tree produced by
# lsystemParser. ctx.accept(self) visits the ctx


class lgrammarVisitor(antlr4.ParseTreeVisitor):

    def aggregateResult(self, aggregate, nextResult):
        if nextResult is None:
            return aggregate

        if aggregate is None:
            return [nextResult]

        aggregate.append(nextResult)
        return aggregate

    def visitTerminal(self, ctx):
        if ctx.symbol.type == lsp.lsystemParser.NT:
            return self.lsystem.get_non_terminal(ctx.getText())
        else:
            return None

    # Visit a parse tree produced by lsystemParser#rotation.
    def visitRotation(self, ctx: lsp.lsystemParser.RotationContext):
        floats = map(lambda x: float(x.getText()), ctx.FLOAT())
        return RotateTerminal(*floats)

    # Visit a parse tree produced by lsystemParser#move.
    def visitMove(self, ctx: lsp.lsystemParser.MoveContext):
        if ctx.FLOAT() is None:
            return MoveTerminal()
        return MoveTerminal(float(ctx.FLOAT().getText()))

    # Visit a parse tree produced by lsystemParser#push.
    def visitPush(self, ctx: lsp.lsystemParser.PushContext):
        return PushTerminal()

    # Visit a parse tree produced by lsystemParser#pop.
    def visitPop(self, ctx: lsp.lsystemParser.PopContext):
        return PopTerminal()

    # Visit a parse tree produced by lsystemParser#terminal.
    def visitTerm(self, ctx: lsp.lsystemParser.TermContext):
        return self.visitChildren(ctx)[0]

    # Visit a parse tree produced by lsystemParser#init_sec.
    def visitInit_sec(self, ctx: lsp.lsystemParser.Init_secContext):
        ctx.init_start().accept(self)

    # Visit a parse tree produced by lsystemParser#init_start.
    def visitInit_start(self, ctx: lsp.lsystemParser.Init_startContext):
        self.lsystem.start = self.lsystem.get_non_terminal(ctx.NT().getText())

    # Visit a parse tree produced by lsystemParser#rule_sec.
    def visitRule_sec(self, ctx: lsp.lsystemParser.Rule_secContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by lsystemParser#rule_entity.
    def visitRule_entity(self, ctx: lsp.lsystemParser.Rule_entityContext):
        self.lsystem.get_non_terminal(
            ctx.NT().getText()).transition = ctx.rule_res().accept(self)

    # Visit a parse tree produced by lsystemParser#rule_res.
    def visitRule_res(self, ctx: lsp.lsystemParser.Rule_resContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by lsystemParser#final_sec.
    def visitFinal_sec(self, ctx: lsp.lsystemParser.Final_secContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by lsystemParser#final_rule_entity.
    def visitFinal_rule_entity(self,
                               ctx:
                               lsp.lsystemParser.Final_rule_entityContext):
        self.lsystem.get_non_terminal(
            ctx.NT().getText()).final_transition = \
            ctx.final_rule_res().accept(self)

    # Visit a parse tree produced by lsystemParser#final_rule_res.
    def visitFinal_rule_res(self,
                            ctx: lsp.lsystemParser.Final_rule_resContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by lsystemParser#code.
    def visitCode(self, ctx: lsp.lsystemParser.CodeContext):
        self.lsystem = Lsystem()
        self.visitChildren(ctx)
        return self.lsystem
