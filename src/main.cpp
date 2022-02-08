#include <cstdlib>
#include <iostream>
#include <parser.hpp>
#include <pkg.hpp>

int main(int argc, char **argv) {
  std::string installType = argv[1];

  if (installType == "help") {
    std::cout
        << "Rice Installer v1.0.0 by Clawbhaiya\n"
        << "Usage:\trci <installType> <target> <function>\n\n"
        << "example: rci git https://github.com/clawbhaiya/rci-test.git bspwm\n"
        << "example: rci tar i3rice.tar.xz i3\n"
        << std::endl;
    return 0;
  }

  if (argc < 3) {
    std::cout << "Error: no target defined." << std::endl;
    return 1;
  }

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
  if (argc < 4) {
    std::cout << "Error: no function defined." << std::endl;
    return 1;
  }
  pkg::ReadIndex(argv[3]);
  return 0;
}
