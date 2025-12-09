#pragma once
#include "Level.h"
#include <functional>

struct LevelData {
    std::function<std::unique_ptr<Level>(b2World&)> factory;
};