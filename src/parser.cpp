#include "utility.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <parser.hpp>
#include <string>
#include <vector>

enum TokenType { Null = 0, Filename = 1, Path = 2, Function = 3, String = 4 };

class token {
public:
  TokenType type;
  std::string value;
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

std::vector<token> tokens;
std::vector<file> files;

// some helper Functions

bool replace(std::string &str, const std::string &from, const std::string &to) {
  size_t start_pos = str.find(from);
  if (start_pos == std::string::npos)
    return false;
  str.replace(start_pos, from.length(), to);
  return true;
}

std::string GetEnv(std::string variable) {
  const char *value = getenv(variable.c_str());
  if (value == nullptr) {
    return "";
  }
  return value;
}

bool fileExist(std::string filename) {
  std::ifstream file;
  file.open(filename);
  if (!file) {
    file.close();
    return false;
  }
  file.close();
  return true;
}

// main Functions

void parser::Parse(std::string line) {
  std::string tok;
  TokenType expected = Function;
  int print = 0;

  for (int i = 0; i < line.length(); i++) {
    tok += line[i];

    if (tok == "print" && expected == Function) {
      tok = "";
      token temp(TokenType::Function, "print");
      tokens.push_back(temp);
      expected = String;
      i++;
    } else if (tok == "endl" && expected == Function) {
      tok = "";
      token temp(TokenType::Function, "endl");
      tokens.push_back(temp);
      expected = Null;
    } else if (i == line.length() - 1) {
      if (expected == String) {
        token temp(TokenType::String, tok);
        tokens.push_back(temp);
      } else if (expected == Path) {
        token temp(TokenType::Path, tok);
        tokens.push_back(temp);
      }
      tok = "";
    } else if (line[i] == '=') {
      tok.pop_back();
      token temp(TokenType::Filename, tok);
      tokens.push_back(temp);
      expected = Path;
      tok = "";
    }
  }
}

void parser::Lex() {
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == Function) {
      if (tokens[i].value == "print") {
        std::cout << tokens[i + 1].value << std::endl;
      } else if (tokens[i].value == "endl") {
        std::cout << std::endl;
      }
    } else if (tokens[i].type == Filename) {
      if (tokens[i + 1].type != Path) {
        std::cout << "ERROR: expected \"Path\"\n";
        return;
      }
      file temp;
      temp.currentLocation = tokens[i].value;
      temp.realLocation = tokens[i + 1].value;
      files.push_back(temp);
      std::cout << tokens[i].value << " -> " << tokens[i + 1].value
                << std::endl;
    }
  }
  tokens.clear();
}

void parser::ParseFiles() {
  std::string tok;
  bool pair = false;
  for (int i = 0; i < files.size(); i++) {
    replace(files[i].realLocation, "$HOME", GetEnv("HOME"));
    if (!fileExist(files[i].currentLocation)) {
      std::cout << "Bad definition in index.sc!\n"
                << "File: " << files[i].currentLocation << " doesn't exist.\n"
                << "Exiting: file not found\n";
      // exit(EXIT_FAILURE);
      return;
    }
    Execute("mv " + files[i].currentLocation + " " + files[i].realLocation);
  }
  files.clear();
}