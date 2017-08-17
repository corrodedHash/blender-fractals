#include "literal.h"
#include "parsing/lsystemBaseVisitor.h"

#include <memory>
#include <stdexcept>

class lgrammarVisitor : public lsystemBaseVisitor {
private:
  NonTerminal *start;
  std::map<std::string, NonTerminal *> nts;
  std::vector<std::string, NTHolder> defines;

public:
  lgrammarVisitor::lgrammarVisitor() : {}
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
    std::string nt_name = ctx->NT->getText();
    if (nts.count(nt_name) > 0) {
      return nts[nt_name];
    } else {
      NonTerminal* result = new NonTerminal(nt_name))
      nts.insert(std::make_pair(nt_name, result);
      return result;
    }
  }

  antlrcpp::Any
  visitDefine_term(lsystemParser::Define_termContext *ctx) override {}

  antlrcpp::Any visitInit_sec(lsystemParser::Init_secContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitInit_start(lsystemParser::Init_startContext *ctx) override {
    start = visitNon_term(ctx->non_term());
  }

  antlrcpp::Any
  visitDefine_sec(lsystemParser::Define_secContext *ctx) override {
    for (const lsystemParser::Define_entityContext *child_ctx :
         ctx->define_entity()) {
      visitDefine_entity(child_ctx);
    }
  }

  antlrcpp::Any
  visitDefine_entity(lsystemParser::Define_entityContext *ctx) override {
    NTHolder resolution = visitDefine_res(ctx->define_res()).as<NTHolder>();
    ins_res = defines.insert(make_pair(ctx->define_term()->DEFINE()->getText(),
                                       std::move(resolution)));
    if (not ins_res.second) {
      throw std::runtime_error("Define already defined")
    }
  }

  antlrcpp::Any
  visitDefine_res(lsystemParser::Define_resContext *ctx) override {
    NTHolder result;
    for (const auto &child : ctx->children) {
      if (antlrcpp::is<Define_termContext>(child)) {
        result.appendHolder(
            visitDefine_term(dynamic_cast<Define_termContext *>(child)));
      } else if (antlrcpp::is<Non_termContext>(child)) {
        result.appendNT(visitNon_term(dynamic_cast<Non_termContext *>(child)));
      } else if (antlrcpp::is<TermContext>(child)) {
        result.appendT(visitTerm(dynamic_cast<TermContext *>(child)));
      }
    }
    return result;
  }

  antlrcpp::Any visitRule_sec(lsystemParser::Rule_secContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitRule_entity(lsystemParser::Rule_entityContext *ctx) override {
    NonTerminal *resolvent = visitNon_term(ctx->non_term());
    resolvent->addTrans(visitRule_res(ctx->rule_res()));
  }

  antlrcpp::Any visitRule_res(lsystemParser::Rule_resContext *ctx) override {
    NTHolder result;
    for (const auto &child : ctx->children) {
      if (antlrcpp::is<Define_termContext>(child)) {
        result.appendHolder(
            visitDefine_term(dynamic_cast<Define_termContext *>(child)));
      } else if (antlrcpp::is<Non_termContext>(child)) {
        result.appendNT(visitNon_term(dynamic_cast<Non_termContext *>(child)));
      } else if (antlrcpp::is<TermContext>(child)) {
        result.appendT(visitTerm(dynamic_cast<TermContext *>(child)));
      }
    }
    return result;
  }

  antlrcpp::Any visitFinal_sec(lsystemParser::Final_secContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitFinal_rule_entity(
      lsystemParser::Final_rule_entityContext *ctx) override {
    NonTerminal *resolvent = visitNon_term(ctx->non_term());
    resolvent->addFinalTrans(visitFinal_rule_res(ctx->rule_res()));
  }

  antlrcpp::Any
  visitFinal_rule_res(lsystemParser::Final_rule_resContext *ctx) override {
    NTHolder result;
    for (const auto &child : ctx->children) {
      if (antlrcpp::is<Define_termContext>(child)) {
        result.appendHolder(
            visitDefine_term(dynamic_cast<Define_termContext *>(child)));
      } else if (antlrcpp::is<Non_termContext>(child)) {
        result.appendNT(visitNon_term(dynamic_cast<Non_termContext *>(child)));
      } else if (antlrcpp::is<TermContext>(child)) {
        result.appendT(visitTerm(dynamic_cast<TermContext *>(child)));
      }
    }
    return result;
  }

  antlrcpp::Any visitCode(lsystemParser::CodeContext *ctx) override {
    return visitChildren(ctx);
  }
}
