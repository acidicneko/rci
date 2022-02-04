#include <cstdlib>
#include <iostream>
#include <parser.hpp>
#include <pkg.hpp>

int main(int argc, char **argv) {
  std::string installType = argv[1];
  pkg::SetCacheFolder();
  if (installType == "tar") {
    pkg::Extract(argv[2]);
  } else if (installType == "git") {
    pkg::Clone(argv[2]);
  } else {
    std::cout << "Error: Unsupported install type: " << installType
              << std::endl;
    exit(EXIT_FAILURE);
  }
  pkg::ReadIndex();
  return 0;
}
