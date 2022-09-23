//
//  supplement.hpp
//  Aviatar
//
//  Created by algasami on 2022/9/17.
//

#ifndef supplement_h
#define supplement_h
#define VK_USE_PLATFORM_MACOS_MVK
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <algorithm>
#include <iostream>
#include <stdexcept>

#include <limits>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include <cstdint>
#include <cstdlib>
#include <cstring>
typedef uint8_t uint2_t;
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

#endif
