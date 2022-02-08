#pragma once

#include <iostream>

namespace pkg {
void Extract(std::string filename);
void Clone(std::string url);
void ReadIndex(std::string functionName);
void SetCacheFolder();
void CleanUp();
std::string GetCacheFolder();
} // namespace pkg
