#pragma once

#include <iostream>

enum TokenType {
  Null = 0,
  Filename = 1,
  Path = 2,
  Function = 3,
  String = 4,
};

class token {
public:
  TokenType type;
  std::string value;
  bool pair = false;
  token(TokenType Type, std::string Value) {
    type = Type;
    value = Value;
  }
};

class file {
public:
  std::string currentLocation;
  std::string realLocation;
};

namespace parser {

void Parse(std::string line);
void Lex();
void LexFunction(std::string functionName);
void ParseFiles(file f);
void ParseFiles();

} // namespace parser
