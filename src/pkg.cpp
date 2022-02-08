#include <fstream>
#include <parser.hpp>
#include <pkg.hpp>
#include <string>
#include <utility.hpp>

std::string cache_folder;

void pkg::SetCacheFolder() {
  cache_folder = GetEnv("HOME") + "/.cache/rci";
  CreateFolder(cache_folder);
}

void pkg::Extract(std::string filename) {
  std::cout << "Extracting package using tar..." << std::endl;
  std::string temp = "tar -xf " + filename + " --directory=" + cache_folder;
  Execute(temp);
}

void pkg::Clone(std::string url) {
  std::cout << "Cloning repository with git..." << std::endl;
  std::string temp = "git clone " + url + " " + cache_folder;
  Execute(temp);
}

void pkg::ReadIndex(std::string functionName) {
  std::cout << "Reading index file..." << std::endl;
  std::ifstream file;
  std::string line;
  std::string index_file_location = cache_folder + "/index.sc";
  file.open(index_file_location);
  while (std::getline(file, line)) {
    parser::Parse(line);
  }
  parser::LexFunction(functionName);
  file.close();
  CleanUp();
}

void pkg::CleanUp() {
  std::cout << "Cleaning up residual files..." << std::endl;
  Execute("rm -rf " + cache_folder);
}

std::string pkg::GetCacheFolder() { return cache_folder; }
