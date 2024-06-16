#pragma once

//Windows API
#include <Windows.h>
#include <String>
#include <vector>
#include <array>
#include <memory>
#include <string>
#include <iostream> 
#include <map>

//Utils
#include "../Utils/Xorstr/Xorstr.hpp"
#include "../Utils/Il2cpp/Il2cpp_Lib.hpp"
#include "../Utils/Math/Vector/Vector.hpp"
#include "../Utils/Math/Matrix/Matrix.hpp"
#include "../Utils/Il2cpp/Managed.hpp"
//Enums
#include "Enums/Enums.hpp"

//Unity
#include "Unity/Rendering/Color/Color.hpp"
#include "Unity/Unity_Sdk.hpp"
#include "Unity/Rendering/Unity_Gui.hpp"

#define DECLARE_MEMBER(type, klass, name) type & name() { FIELD(klass, ##name) return *reinterpret_cast<type*>(this + name); }

//Classes
#include "Classes/BaseWeapon.hpp"
#include "Classes/Transform.hpp"
#include "Classes/BasePlayer.hpp"

//Features
#include "../Rust/Features/Visuals/Visuals.hpp"



