#include "ExprParser.h"
#include "ExprVisitor.h"

#include <iostream>

class EvalVisitor : public ExprVisitor {
public:

  std::any visitCalc(ExprParser::CalcContext *ctx) override {
    return visit(ctx->expr());
    /// TODO
  }

  std::any visitMulDiv(ExprParser::MulDivContext *ctx) override {
    int left = std::any_cast<int>(visit(ctx->expr(0)));
    int right = std::any_cast<int>(visit(ctx->expr(1)));
    if(ctx->op->getType() == ExprParser::MUL) {
      return left * right;
    } else {
      return left / right;
    }

    /// TODO
  }

  std::any visitAddSub(ExprParser::AddSubContext *ctx) override {
    int left = std::any_cast<int>(visit(ctx->expr(0)));
    int right = std::any_cast<int>(visit(ctx->expr(1)));
    if(ctx->op->getType() == ExprParser::ADD) {
      return left + right;
    } else {
      return left - right;
    }
    /// TODO
  }

  std::any visitInt(ExprParser::IntContext *ctx) override {
    return std::stoi(ctx->INT()->getText());
    /// TODO
  }

  std::any visitParens(ExprParser::ParensContext *ctx) override {
    return visit(ctx->expr());
    /// TODO
  }

};
