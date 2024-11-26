/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"
#include <memory>



/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                continue;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

// void processLine(std::string line, Program &program, EvalState &state) {
//     TokenScanner scanner;
//     scanner.ignoreWhitespace();
//     scanner.scanNumbers();
//     scanner.setInput(line);
//     if(scanner.hasMoreTokens()) {
//         std::string token=scanner.nextToken();
//         if(isdigit(token[0])) {
//             //program line
//             int LineNumber=stringToInteger(token);
//             program.setEndState(false);
//             if(scanner.hasMoreTokens()) {
//                 std::string token=scanner.nextToken();
//                 if(token=="LET") {
//                     Statement *stmt =new LetStatement(scanner);
//                     program.addSourceLine(LineNumber,line);
//                     program.setParsedStatement(LineNumber,stmt);
//                     //delete stmt;
//                 }else if(token=="PRINT") {
//                     Statement *stmt =new PrintStatement(scanner);
//                     program.addSourceLine(LineNumber,line);
//                     program.setParsedStatement(LineNumber,stmt);
//                     //delete stmt;
//                 }else if(token=="INPUT") {
//                     Statement *stmt =new InputStatement(scanner);
//                     program.addSourceLine(LineNumber,line);
//                     program.setParsedStatement(LineNumber,stmt);
//                     //delete stmt;
//                 }else if(token=="GOTO") {
//                     Statement *stmt =new GotoStatement(scanner);
//                     program.addSourceLine(LineNumber,line);
//                     program.setParsedStatement(LineNumber,stmt);
//                     //delete stmt;
//                 }else if(token=="IF") {
//                     Statement *stmt =new IfStatement(scanner);
//                     program.addSourceLine(LineNumber,line);
//                     program.setParsedStatement(LineNumber,stmt);
//                     //delete stmt;
//                 }else if(token=="END") {
//                     Statement *stmt =new EndStatement(scanner);
//                     program.addSourceLine(LineNumber,line);
//                     program.setParsedStatement(LineNumber,stmt);
//                     //delete stmt;
//                 }else if(token=="REM") {
//                     Statement *stmt =new RemStatement(scanner);
//                     program.addSourceLine(LineNumber,line);
//                     program.setParsedStatement(LineNumber,stmt);
//                     //delete stmt;
//                 }else {
//                     error("SYNTAX ERROR");
//                 }
//             }else {
//                 program.removeSourceLine(LineNumber);
//             }
//         }else {
//             //command
//             if(token=="RUN") {
//                 int LineNumber=program.getFirstLineNumber();
//                 program.setCurrentLine(LineNumber);
//                 while(!program.getEndState()&&LineNumber!=-1) {
//                     Statement *stmt=program.getParsedStatement(LineNumber);
//                     stmt->execute(state,program);
//                     LineNumber=program.getCurrentLine();
//                     //delete stmt;
//                 }
//                 program.setEndState(false);
//             }else if(token=="LIST") {
//                 int LineNumber=program.getFirstLineNumber();
//                 while(LineNumber!=-1) {
//                     std::cout<<program.getSourceLine(LineNumber)<<std::endl;
//                     LineNumber=program.getNextLineNumber(LineNumber);
//                 }
//             }else if(token=="CLEAR") {
//                 program.clear();
//                 state.Clear();
//             }else if(token=="QUIT") {
//                 exit(0);
//             }else if(token=="HELP") {
//                 std::cout<<"Yet another basic interpreter"<<std::endl;
//             }else if(token=="LET") {
//                 Statement *stmt =new LetStatement(scanner);
//                 stmt->execute(state,program);
//                 delete stmt;
//             }else if(token=="PRINT") {
//                 Statement *stmt =new PrintStatement(scanner);
//                 stmt->execute(state,program);
//                 delete stmt;
//             }else if(token=="INPUT") {
//                 Statement *stmt =new InputStatement(scanner);
//                 stmt->execute(state,program);
//                 delete stmt;
//             }else {
//                 error("SYNTAX ERROR");
//             }
//
//         }
//
//     }
//
//
//
//     //todo
// }
void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    if (scanner.hasMoreTokens()) {
        std::string token = scanner.nextToken();
        if (isdigit(token[0])) {
            // program line
            int LineNumber = stringToInteger(token);
            program.setEndState(false);
            if (scanner.hasMoreTokens()) {
                std::string token = scanner.nextToken();
                std::unique_ptr<Statement> stmt;
                if (token == "LET") {
                    stmt = std::make_unique<LetStatement>(scanner);
                } else if (token == "PRINT") {
                    stmt = std::make_unique<PrintStatement>(scanner);
                } else if (token == "INPUT") {
                    stmt = std::make_unique<InputStatement>(scanner);
                } else if (token == "GOTO") {
                    stmt = std::make_unique<GotoStatement>(scanner);
                } else if (token == "IF") {
                    stmt = std::make_unique<IfStatement>(scanner);
                } else if (token == "END") {
                    stmt = std::make_unique<EndStatement>(scanner);
                } else if (token == "REM") {
                    stmt = std::make_unique<RemStatement>(scanner);
                } else {
                    error("SYNTAX ERROR");
                }
                if (stmt) {
                    program.addSourceLine(LineNumber, line);
                    program.setParsedStatement(LineNumber, std::move(stmt));
                }
            } else {
                program.removeSourceLine(LineNumber);
            }
        } else {
            // command
            if (token == "RUN") {
                int LineNumber = program.getFirstLineNumber();
                program.setCurrentLine(LineNumber);
                while (!program.getEndState() && LineNumber != -1) {
                    Statement *stmt = program.getParsedStatement(LineNumber);
                    stmt->execute(state, program);
                    LineNumber = program.getCurrentLine();
                }
                program.setEndState(false);
            } else if (token == "LIST") {
                int LineNumber = program.getFirstLineNumber();
                while (LineNumber != -1) {
                    std::cout << program.getSourceLine(LineNumber) << std::endl;
                    LineNumber = program.getNextLineNumber(LineNumber);
                }
            } else if (token == "CLEAR") {
                program.clear();
                state.Clear();
            } else if (token == "QUIT") {
                exit(0);
            } else if (token == "HELP") {
                std::cout << "Yet another basic interpreter" << std::endl;
            } else if (token == "LET") {
                auto stmt = std::make_unique<LetStatement>(scanner);
                stmt->execute(state, program);
            } else if (token == "PRINT") {
                auto stmt = std::make_unique<PrintStatement>(scanner);
                stmt->execute(state, program);
            } else if (token == "INPUT") {
                auto stmt = std::make_unique<InputStatement>(scanner);
                stmt->execute(state, program);
            } else {
                error("SYNTAX ERROR");
            }
        }
    }
}