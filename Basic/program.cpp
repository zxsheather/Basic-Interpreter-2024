/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"



Program::Program() = default;

Program::~Program() {
    clear();
}

void Program::clear() {
    lineNumbers.clear();
    sourceLines.clear();
    parsedLines.clear();
    // Replace this stub with your own code
    //todo
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    lineNumbers.insert(lineNumber);
    sourceLines[lineNumber] = line;
    //todo
}

void Program::removeSourceLine(int lineNumber) {
    lineNumbers.erase(lineNumber);
    sourceLines.erase(lineNumber);
    //todo
}

std::string Program::getSourceLine(int lineNumber) {
    return sourceLines[lineNumber];
    // Replace this stub with your own code
    //todo
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if(lineNumbers.find(lineNumber)!=lineNumbers.end()) {
        parsedLines[lineNumber] = stmt;
    }else {
        error("LINE NUMBER ERROR");
    }
    //todo
}


Statement *Program::getParsedStatement(int lineNumber) {
    if(lineNumbers.find(lineNumber)!=lineNumbers.end()) {
        return parsedLines[lineNumber];
    }else {
        return nullptr;
    }
   //todo
}

int Program::getFirstLineNumber() {
    if(lineNumbers.empty()) {
        return -1;
    }else {
        return *lineNumbers.begin();
    }
    // Replace this stub with your own code
    //todo
}

int Program::getNextLineNumber(int lineNumber) {
    if(lineNumbers.find(lineNumber)==lineNumbers.end()) {
        return -1;
    }else {
        auto it = lineNumbers.upper_bound(lineNumber);
        if(it==lineNumbers.end()) {
            currentLine=-1;
            return -1;
        }else {
            setCurrentLine(*it);
            return *it;
        }
    }
    //todo
}

void Program::setCurrentLine(int lineNumber) {
    if(lineNumbers.find(lineNumber)!=lineNumbers.end()) {
        currentLine = lineNumber;
    }else {
        error("LINE NUMBER ERROR");
    }
    //todo
}

int Program::getCurrentLine() const {
    return currentLine;
}

void Program::setEndState(bool state) {
    end_state = state;
    //todo
}

bool Program::getEndState() {
    return end_state;
    //todo
}
//more func to add
//todo


