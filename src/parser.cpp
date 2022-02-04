#include "pkg.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <parser.hpp>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <utility.hpp>
#include <vector>

std::vector<token> tokens;

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
    } else if (tok == "exec" && expected == Function) {
      tok = "";
      token temp(TokenType::Function, "exec");
      tokens.push_back(temp);
      expected = String;
      i++;
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
      } else if (tokens[i].value == "exec") {
        Execute(tokens[i + 1].value);
      }
    } else if (tokens[i].type == Filename) {
      if (tokens[i + 1].type != Path) {
        std::cout << "ERROR: expected \"Path\"" << std::endl;
        return;
      }
      file temp;
      temp.currentLocation = tokens[i].value;
      temp.realLocation = tokens[i + 1].value;
      parser::ParseFiles(temp);
    }
  }
  tokens.clear();
}

void parser::ParseFiles(file f) {
  std::cout << f.currentLocation << " -> " << f.realLocation << std::endl;
  f.currentLocation.insert(0, pkg::GetCacheFolder() + "/");
  replace(f.realLocation, "$HOME", GetEnv("HOME"));

  if (!fileExist(f.currentLocation)) {
    std::cout << "Bad definition in index.sc!\n"
              << "File: " << f.currentLocation << " doesn't exist.\n"
              << "Exiting: file not found" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!folderExist(f.realLocation)) {
    std::cout << "Folder: " << getFolderName(f.realLocation)
              << " doesn't exists!\n"
              << "Creating folder..." << std::endl;
    std::string mkdirCmd = "mkdir -p " + getFolderName(f.realLocation);
    Execute(mkdirCmd);
  }

  Execute("mv " + f.currentLocation + " " + f.realLocation);
}
