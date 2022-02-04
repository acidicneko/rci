#pragma once

#include <iostream>

namespace pkg {
void Extract(std::string filename);
void Clone(std::string url);
void ReadIndex();
void SetCacheFolder();
void CleanUp();
std::string GetCacheFolder();
} // namespace pkg
