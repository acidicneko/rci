#include "parser.hpp"
#include <iostream>
#include <pkg.hpp>


int main(int argc, char** argv){
    pkg::Extract(argv[1]);
    pkg::ReadIndex();
    parser::ParseFiles();
    return 0;
}
