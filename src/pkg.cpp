#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <parser.hpp>
#include <pkg.hpp>
#include <string>
#include <utility.hpp>

std::string cache_folder;

void pkg::SetCacheFolder() {
  cache_folder = GetEnv("HOME") + "/.cache/rci";
  std::filesystem::path cache_folder_path = cache_folder;
  if (std::filesystem::is_directory(cache_folder_path)) {
    std::cout << "Info: junk cache found." << std::endl;
    pkg::CleanUp();
  }
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
  std::string index_file_location = cache_folder + "/index.rci";
  file.open(index_file_location);
  if (!file) {
    std::cout << "Error: index.rci not found." << std::endl;
    pkg::CleanUp();
    exit(EXIT_FAILURE);
  }
  while (std::getline(file, line)) {
    parser::Parse(line);
  }
  parser::LexFunction(functionName);
  file.close();
}

void pkg::CleanUp() {
  std::cout << "Cleaning up residual files..." << std::endl;
  Execute("rm -rf " + cache_folder);
}

std::string pkg::GetCacheFolder() { return cache_folder; }
