/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"


/* Implementation of the Statement class */

//int stringToInt(std::string str) ;

Statement::Statement() = default;

Statement::~Statement() = default;


RemStatement::RemStatement(TokenScanner &scanner) {
  comment = "";
  while (scanner.hasMoreTokens()) {
    comment += scanner.nextToken() + " ";
  }
}

void RemStatement::execute(EvalState &state, Program &program) {
  program.getNextLineNumber(program.getCurrentLine());
}

RemStatement::~RemStatement() = default;

LetStatement::LetStatement(TokenScanner &scanner) {
  var = scanner.nextToken();
  if (var == "LET" || var == "PRINT" || var == "INPUT" || var == "GOTO" || var == "IF" || var == "END" || var == "REM"
      || var == "RUN" || var == "LIST" || var == "CLEAR" || var == "QUIT" || var == "HELP") {
    error("SYNTAX ERROR");
  }
  if (scanner.nextToken() != "=") {
    error("SYNTAX ERROR");
  }
  exp = parseExp(scanner);
}

void LetStatement::execute(EvalState &state, Program &program) {
  int value = exp->eval(state);
  state.setValue(var, value);
  program.getNextLineNumber(program.getCurrentLine());
}

LetStatement::~LetStatement() {
  delete exp;
  //exp=nullptr;
}

PrintStatement::PrintStatement(TokenScanner &scanner) {
  exp = parseExp(scanner);
}

void PrintStatement::execute(EvalState &state, Program &program) {
  int value = exp->eval(state);
  std::cout << value << std::endl;
  program.getNextLineNumber(program.getCurrentLine());
}

PrintStatement::~PrintStatement() {
  delete exp;
}

InputStatement::InputStatement(TokenScanner &scanner) {
  var = scanner.nextToken();
}

bool isNumber(std::string str) {
  for (int i = 0; i < str.length(); i++) {
    if ((str[i] < '0' || str[i] > '9') && !(i == 0 && str[i] == '-')) {
      return false;
    }
  }
  return true;
}

void InputStatement::execute(EvalState &state, Program &program) {
  std::string input;
  std::cout << " ? ";
  getline(std::cin, input);
  while (!isNumber(input)) {
    std::cout << "INVALID NUMBER" << std::endl;
    std::cout << " ? ";
    std::cin >> input;
  }
  state.setValue(var, stringToInteger(input));
  program.getNextLineNumber(program.getCurrentLine());
}

InputStatement::~InputStatement() = default;

GotoStatement::GotoStatement(TokenScanner &scanner) {
  lineNumber = stringToInteger(scanner.nextToken());
}

void GotoStatement::execute(EvalState &state, Program &program) {
  program.setCurrentLine(lineNumber);
}

GotoStatement::~GotoStatement() = default;

IfStatement::IfStatement(TokenScanner &scanner) {
  std::string scanner1 = "";
  std::string scanner2 = scanner.nextToken();
  while (true) {
    scanner1 += scanner2;
    if (!scanner.hasMoreTokens()) {
      delete lhs;
      delete rhs;
      error("SYNTAX ERROR");
    }
    scanner2 = scanner.nextToken();
    if (scanner2 == "=" || scanner2 == "<" || scanner2 == ">") {
      break;
    }
  }
  TokenScanner scanner3 = scanner1;
  lhs = parseExp(scanner3);
  op = scanner2;
  scanner2 = scanner.nextToken();
  scanner1 = "";
  while (scanner2 != "THEN") {
    scanner1 += scanner2;
    if (!scanner.hasMoreTokens()) {
      delete lhs;
      delete rhs;
      error("SYNTAX ERROR");
    }
    scanner2 = scanner.nextToken();
  }
  TokenScanner scanner4 = scanner1;
  rhs = parseExp(scanner4);
  lineNumber = stringToInteger(scanner.nextToken());
}

void IfStatement::execute(EvalState &state, Program &program) {
  int lhsValue = lhs->eval(state);
  int rhsValue = rhs->eval(state);
  bool condition = false;

  if (op == "=") {
    condition = (lhsValue == rhsValue);
  } else if (op == "<") {
    condition = (lhsValue < rhsValue);
  } else if (op == ">") {
    condition = (lhsValue > rhsValue);
  } else {
    delete lhs;
    delete rhs;
    error("SYNTAX ERROR");
  }
  if (condition) {
    program.setCurrentLine(lineNumber);
  } else {
    program.getNextLineNumber(program.getCurrentLine());
  }
}

IfStatement::~IfStatement() {
  delete lhs;
  delete rhs;
}

EndStatement::EndStatement(TokenScanner &scanner) {
  //do nothing
}

void EndStatement::execute(EvalState &state, Program &program) {
  program.setEndState(true);
}

EndStatement::~EndStatement() = default;


//todo