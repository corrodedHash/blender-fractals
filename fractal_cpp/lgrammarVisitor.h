#pragma once
#ifndef LGRAMMARVISITOR_H
#define LGRAMMARVISITOR_H


#include "literal.h"
#include "parsing/lsystemBaseVisitor.h"

#include <memory>
#include <stdexcept>
#include <map>


struct NonTerminalManager {
  NonTerminal* start;
  std::vector<NonTerminal*> nts;
  ~NonTerminalManager(){
    for (NonTerminal* it: nts){
      delete it;
    }
  }
};

class lgrammarVisitor : public lsystemBaseVisitor {
private:
  NonTerminalManager ntm;
  std::map<std::string, NonTerminal *> nts;
  std::map<std::string, NTHolder> defines;

public:
  lgrammarVisitor() {}

  template <typename U> NTHolder buildTrans(U *ctx);

  antlrcpp::Any
  visitProbability(lsystemParser::ProbabilityContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitRand_entry(lsystemParser::Rand_entryContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitRotation(lsystemParser::RotationContext *ctx) override {
    return Terminal(Terminal::ROTATE_TERM);
  }

  antlrcpp::Any visitMove(lsystemParser::MoveContext *ctx) override {
    return Terminal(Terminal::MOVE_TERM);
  }

  antlrcpp::Any visitDraw(lsystemParser::DrawContext *ctx) override {
    return Terminal(Terminal::DRAW_TERM);
  }

  antlrcpp::Any visitPush(lsystemParser::PushContext *ctx) override {
    return Terminal(Terminal::PUSH_TERM);
  }

  antlrcpp::Any visitPop(lsystemParser::PopContext *ctx) override {
    return Terminal(Terminal::POP_TERM);
  }

  antlrcpp::Any visitTerm(lsystemParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitNon_term(lsystemParser::Non_termContext *ctx) override {
    std::string nt_name = ctx->NT()->getText();
    if (nts.count(nt_name) > 0) {
      return nts[nt_name];
    } else {
      NonTerminal *result = new NonTerminal(nt_name);
      nts.insert(std::make_pair(nt_name, result));
      ntm.nts.push_back(result);
      return result;
    }
  }

  antlrcpp::Any
  visitDefine_term(lsystemParser::Define_termContext *ctx) override {
    std::string def_name = ctx->DEFINE()->getText();
    if (nts.count(def_name) > 0) {
      return defines[def_name];
    } else {
      throw std::runtime_error("Define used is undefined");
    }
  }

  antlrcpp::Any visitInit_sec(lsystemParser::Init_secContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitInit_start(lsystemParser::Init_startContext *ctx) override {
    ntm.start = visitNon_term(ctx->non_term());
    return nullptr;
  }

  antlrcpp::Any
  visitDefine_sec(lsystemParser::Define_secContext *ctx) override {
    for (lsystemParser::Define_entityContext *child_ctx :
         ctx->define_entity()) {
      visitDefine_entity(child_ctx);
    }
    return nullptr;
  }

  antlrcpp::Any
  visitDefine_entity(lsystemParser::Define_entityContext *ctx) override {
    NTHolder resolution = visitDefine_res(ctx->define_res()).as<NTHolder>();
    auto ins_res = defines.insert(make_pair(
        ctx->define_term()->DEFINE()->getText(), std::move(resolution)));
    if (not ins_res.second) {
      throw std::runtime_error("Define already defined");
    }
    return nullptr;
  }

  antlrcpp::Any
  visitDefine_res(lsystemParser::Define_resContext *ctx) override {
    return buildTrans(ctx);
  }

  antlrcpp::Any visitRule_sec(lsystemParser::Rule_secContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitRule_entity(lsystemParser::Rule_entityContext *ctx) override {
    NonTerminal *resolvent = visitNon_term(ctx->non_term());
    resolvent->addTrans(visitRule_res(ctx->rule_res()));
    return nullptr;
  }

  antlrcpp::Any visitRule_res(lsystemParser::Rule_resContext *ctx) override {
    return buildTrans(ctx);
  }

  antlrcpp::Any visitFinal_sec(lsystemParser::Final_secContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitFinal_rule_entity(
      lsystemParser::Final_rule_entityContext *ctx) override {
    NonTerminal *resolvent = visitNon_term(ctx->non_term());
    resolvent->addFinalTrans(visitFinal_rule_res(ctx->final_rule_res()));
    return nullptr;
  }

  antlrcpp::Any
  visitFinal_rule_res(lsystemParser::Final_rule_resContext *ctx) override {
    return buildTrans(ctx);
  }

  antlrcpp::Any visitCode(lsystemParser::CodeContext *ctx) override {
    visitChildren(ctx);
    return ntm;
  }
};

#endif /* end of include guard: lgrammarVisitor */
