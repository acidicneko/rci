#pragma once
#include <iostream>

void Execute(std::string command);
bool replace(std::string &str, const std::string &from, const std::string &to);
std::string GetEnv(std::string variable);
bool fileExist(std::string filename);
bool folderExist(std::string folderFromFile);
std::string getFolderName(std::string fullPath);
void CreateFolder(std::string folderPath);
