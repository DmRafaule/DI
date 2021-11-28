#pragma once

// #define DEBUG
#include <memory>

template<typename T> using Ref = std::shared_ptr<T>;
template<typename T> using Scope = std::unique_ptr<T>;
#define C_Ref 	std::make_shared
#define C_Scope std::make_unique

