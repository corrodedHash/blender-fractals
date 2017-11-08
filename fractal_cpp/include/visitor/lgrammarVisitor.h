#pragma once
#ifndef LGRAMMARVISITOR_H
#define LGRAMMARVISITOR_H

#include "visitor/literal.h"
// Generated headerfile
#include "lsystemParserBaseVisitor.h"

#include <map>
#include <memory>
#include <stdexcept>

struct NonTerminalManager {
  NonTerminal* start;
  std::vector<std::shared_ptr<NonTerminal>> nts;
};
namespace antlr {
class lgrammarVisitor : public lsystemParserBaseVisitor {
  private:
  NonTerminalManager ntm;
  std::map<std::string, NonTerminal*> nts;
  std::map<std::string, NTHolder> defines;

  public:
  lgrammarVisitor() {}

  template <typename U>
  NTHolder buildTrans(U* ctx)
  {
    NTHolder result;
    for (const auto& child : ctx->children) {
      if (antlrcpp::is<lsystemParser::Define_termContext*>(child)) {
        result.appendHolder(visitDefine_term(
            dynamic_cast<lsystemParser::Define_termContext*>(child)));
      } else if (antlrcpp::is<lsystemParser::Non_termContext*>(child)) {
        result.appendNT(
            visitNon_term(dynamic_cast<lsystemParser::Non_termContext*>(child)));
      } else if (antlrcpp::is<lsystemParser::TermContext*>(child)) {
        result.appendT(
            visitTerm(dynamic_cast<lsystemParser::TermContext*>(child)));
      }
    }
    return result;
  }

  antlrcpp::Any
  visitProbability(lsystemParser::ProbabilityContext* ctx) override
  {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitRand_entry(lsystemParser::Rand_entryContext* ctx) override
  {
    std::array<double, 2> result;
    result[0] = std::stod(ctx->FLOAT(0)->getText());
    if (ctx->FLOAT().size() > 1) {
      result[1] = std::stod(ctx->FLOAT(1)->getText());
    } else {
      result[1] = result[0];
    }
    return result;
  }

  antlrcpp::Any visitRotation(lsystemParser::RotationContext* ctx) override
  {
    Terminal result(Terminal::ROTATE_TERM);
    result.values[0] = 0;
    result.values[1] = 0;
    result.values[2] = 0;
    std::array<double, 2> rand_number;
    switch (ctx->rand_entry().size()) {
    case 3:
      rand_number = visitRand_entry(dynamic_cast<lsystemParser::Rand_entryContext*>(ctx->rand_entry(2)));
      result.values[4] = rand_number[0];
      result.values[5] = rand_number[1];
    case 2:
      rand_number = visitRand_entry(dynamic_cast<lsystemParser::Rand_entryContext*>(ctx->rand_entry(1)));
      result.values[2] = rand_number[0];
      result.values[3] = rand_number[1];
    case 1:
      rand_number = visitRand_entry(dynamic_cast<lsystemParser::Rand_entryContext*>(ctx->rand_entry(0)));
      result.values[0] = rand_number[0];
      result.values[1] = rand_number[1];
      break;
    case 0:
      result.values[0] = 90.0;
      result.values[1] = 90.0;
      break;
    default:
      std::cout << ctx->rand_entry().size();
      throw std::runtime_error("rotate entry weird");
    }
    return result;
  }

  antlrcpp::Any visitMove(lsystemParser::MoveContext* ctx) override
  {
    Terminal result(Terminal::MOVE_TERM);
    std::array<double, 2> rand_number;
    rand_number = visitRand_entry(dynamic_cast<lsystemParser::Rand_entryContext*>(ctx->rand_entry()));
    result.values[0] = rand_number[0];
    result.values[1] = rand_number[1];
    return result;
  }

  antlrcpp::Any visitDraw(lsystemParser::DrawContext* ctx) override
  {
    Terminal result(Terminal::DRAW_TERM);
    std::array<double, 2> rand_number;
    rand_number = visitRand_entry(dynamic_cast<lsystemParser::Rand_entryContext*>(ctx->rand_entry()));
    result.values[0] = rand_number[0];
    result.values[1] = rand_number[1];
    return result;
  }

  antlrcpp::Any visitFace(lsystemParser::FaceContext* ctx) override
  {
    Terminal result(Terminal::FACE_TERM);
    std::array<double, 2> rand_number;
    rand_number = visitRand_entry(dynamic_cast<lsystemParser::Rand_entryContext*>(ctx->rand_entry()));
    result.values[0] = rand_number[0];
    result.values[1] = rand_number[1];
    return result;
  }

  antlrcpp::Any visitEndface(lsystemParser::EndfaceContext* ctx) override
  {
    return Terminal(Terminal::ENDFACE_TERM);
  }
  antlrcpp::Any visitPush(lsystemParser::PushContext* ctx) override
  {
    return Terminal(Terminal::PUSH_TERM);
  }

  antlrcpp::Any visitPop(lsystemParser::PopContext* ctx) override
  {
    return Terminal(Terminal::POP_TERM);
  }

  antlrcpp::Any visitTerm(lsystemParser::TermContext* ctx) override
  {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitNon_term(lsystemParser::Non_termContext* ctx) override
  {
    std::string nt_name = ctx->NT()->getText();
    if (nts.count(nt_name) > 0) {
      return nts[nt_name];
    } else {
      ntm.nts.push_back(std::make_shared<NonTerminal>(nt_name));
      nts.insert(std::make_pair(nt_name, ntm.nts.back().get()));
      return ntm.nts.back().get();
    }
  }

  antlrcpp::Any
  visitDefine_term(lsystemParser::Define_termContext* ctx) override
  {
    std::string def_name = ctx->DEFINE()->getText();
    if (defines.count(def_name) > 0) {
      return defines[def_name];
    } else {
      throw std::runtime_error("Define used is undefined");
    }
  }

  antlrcpp::Any visitInit_sec(lsystemParser::Init_secContext* ctx) override
  {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitInit_start(lsystemParser::Init_startContext* ctx) override
  {
    ntm.start = visitNon_term(ctx->non_term());
    return nullptr;
  }

  antlrcpp::Any
  visitDefine_sec(lsystemParser::Define_secContext* ctx) override
  {
    for (lsystemParser::Define_entityContext* child_ctx :
        ctx->define_entity()) {
      visitDefine_entity(child_ctx);
    }
    return nullptr;
  }

  antlrcpp::Any
  visitDefine_entity(lsystemParser::Define_entityContext* ctx) override
  {
    NTHolder resolution = visitDefine_res(ctx->define_res()).as<NTHolder>();
    auto ins_res = defines.insert(make_pair(
        ctx->define_term()->DEFINE()->getText(), std::move(resolution)));
    if (not ins_res.second) {
      throw std::runtime_error("Define already defined");
    }
    return nullptr;
  }

  antlrcpp::Any
  visitDefine_res(lsystemParser::Define_resContext* ctx) override
  {
    return buildTrans(ctx);
  }

  antlrcpp::Any visitRule_sec(lsystemParser::Rule_secContext* ctx) override
  {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitRule_entity(lsystemParser::Rule_entityContext* ctx) override
  {
    NonTerminal* resolvent = visitNon_term(ctx->non_term());
    resolvent->addTrans(visitRule_res(ctx->rule_res()));
    return nullptr;
  }

  antlrcpp::Any visitRule_res(lsystemParser::Rule_resContext* ctx) override
  {
    return buildTrans(ctx);
  }

  antlrcpp::Any visitFinal_sec(lsystemParser::Final_secContext* ctx) override
  {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitFinal_rule_entity(
      lsystemParser::Final_rule_entityContext* ctx) override
  {
    NonTerminal* resolvent = visitNon_term(ctx->non_term());
    resolvent->addFinalTrans(visitFinal_rule_res(ctx->final_rule_res()));
    return nullptr;
  }

  antlrcpp::Any
  visitFinal_rule_res(lsystemParser::Final_rule_resContext* ctx) override
  {
    return buildTrans(ctx);
  }

  antlrcpp::Any visitCode(lsystemParser::CodeContext* ctx) override
  {
    visitChildren(ctx);
    return ntm;
  }
};
}
#endif /* end of include guard: lgrammarVisitor */
