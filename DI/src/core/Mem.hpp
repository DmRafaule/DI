#pragma once

// #define DEBUG
#include <memory>

template<typename T> using Ref = std::shared_ptr<T>;
template<typename T> using Scope = std::unique_ptr<T>;
#define C_Ref 	std::make_shared
#define C_Scope std::make_unique
#define GET_GLOBAL_DATA  namespace DI{\
    extern Scope<DI::AppData> _appData;\
    extern Scope<DI::WinData> _winData;\
    extern Scope<DI::GUIData> _guiData;\
}
