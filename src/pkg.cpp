#include <parser.hpp>
#include <pkg.hpp>
#include <string>
#include <utility.hpp>
#include <fstream>

void pkg::Extract(std::string filename){
    std::string temp = "tar -xf " + filename;
    Execute(temp);
}

void pkg::Clone(std::string url){
    std::string temp = "git clone " + url;
    Execute(temp);
}

void pkg::ReadIndex(){
    std::ifstream file;
    std::string line;
    file.open("index.sc");
    while(std::getline(file, line)){
        parser::Parse(line);
        parser::Lex();
    }

}
