// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here

#include <string>
#include <array>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <fstream>

#include <iostream>
#include <chrono>


#include "Config.h"
#include "Logger/Log.h"

#ifdef DEBUG
#define ASSERT(x) {if (!x) { printf("ASSERTION FAILED"); __debugbreak();}};
#else
#define ASSERT(x)
#endif

#endif //PCH_H
