#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace DI{

std::unordered_map<std::string,std::vector<std::string>> ListDirectory(const std::string path);

};