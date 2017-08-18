#include "lgrammarVisitor.h"

template <typename U> NTHolder lgrammarVisitor::buildTrans(U *ctx) {
  NTHolder result;
  for (const auto &child : ctx->children) {
    if (antlrcpp::is<lsystemParser::Define_termContext *>(child)) {
      result.appendHolder(visitDefine_term(
          dynamic_cast<lsystemParser::Define_termContext *>(child)));
    } else if (antlrcpp::is<lsystemParser::Non_termContext *>(child)) {
      result.appendNT(
          visitNon_term(dynamic_cast<lsystemParser::Non_termContext *>(child)));
    } else if (antlrcpp::is<lsystemParser::TermContext *>(child)) {
      result.appendT(
          visitTerm(dynamic_cast<lsystemParser::TermContext *>(child)));
    }
  }
  return result;
}
