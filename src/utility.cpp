#include <utility.hpp>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>

void Execute(std::string command){
    char* temp = (char*)command.c_str();
    char* argv[200];
    int argc = 0;
    argv[argc] = std::strtok(temp, " ");
    while(argv[argc]){
        argc++;
        argv[argc] = std::strtok(0, " ");
    }
    
    int status;
    if(fork() == 0){
        execvp(argv[0], argv);
    } else {
        wait(&status);
    }
}
