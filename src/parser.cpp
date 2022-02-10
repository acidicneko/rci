#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <parser.hpp>
#include <pkg.hpp>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <utility.hpp>
#include <vector>

std::vector<token> tokens;

void parser::Parse(std::string line) {
  std::string tok;
  TokenType expected = Function;
  replace(line, "$HOME", GetEnv("HOME"));
  replace(line, "$RCI", pkg::GetCacheFolder());
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
    } else if (tok == "start" && expected == Function) {
      tok = "";
      token temp(TokenType::Function, "start");
      tokens.push_back(temp);
      expected = String;
      i++;
    } else if (tok == "stop" && expected == Function) {
      tok = "";
      token temp(TokenType::Function, "stop");
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

void parser::LexFunction(std::string functionName) {
  bool functionRunning = false;
  std::vector<token> localTokens;
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i].value == "start" && tokens[i + 1].value == functionName) {
      functionRunning = true;
      continue;
    } else if (tokens[i].value == "stop") {
      if (tokens[i + 1].value != functionName && i == tokens.size()) {
        std::cout << "error: section end not found: " << functionName
                  << std::endl;
        exit(EXIT_FAILURE);
      }
      if (tokens[i + 1].value == functionName)
        break;
    } else if (functionRunning) {
      localTokens.push_back(tokens[i]);
    }
  }
  if (!functionRunning) {
    std::cout << "error: section: " << functionName << " not found"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < localTokens.size(); i++) {
    if (localTokens[i].type == Function) {
      if (localTokens[i].value == "print") {
        std::cout << localTokens[i + 1].value << std::endl;
      } else if (localTokens[i].value == "endl") {
        std::cout << std::endl;
      } else if (localTokens[i].value == "exec") {
        Execute(localTokens[i + 1].value);
      }
    } else if (localTokens[i].type == Filename) {
      if (localTokens[i + 1].type != Path) {
        std::cout << "ERROR: expected \"Path\"" << std::endl;
        return;
      }
      file temp;
      temp.currentLocation = localTokens[i].value;
      temp.realLocation = localTokens[i + 1].value;
      parser::ParseFiles(temp);
    }
  }
  tokens.clear();
  localTokens.clear();
}

void parser::ParseFiles(file f) {
  std::cout << f.currentLocation << " -> " << f.realLocation << std::endl;
  f.currentLocation.insert(0, pkg::GetCacheFolder() + "/");
  // replace(f.realLocation, "$HOME", GetEnv("HOME"));

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
