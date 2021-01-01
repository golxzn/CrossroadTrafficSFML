#ifndef PLATFORM_H
#define PLATFORM_H

//============== CPP =============//
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <memory>
#include <algorithm>

#include <thread>
#include <mutex>
#include <atomic>

//============= SFML =============//
#include <SFML/Graphics.hpp>

#ifdef WIN32
    using uint = uint32_t;
    using id_t = int32_t;
#endif

#endif // PLATFORM_H
