#pragma once
#include "vector"

class Road {

public:
    float minY = -400;
    float maxY = 800;
    float center = 200;
    std::vector<float> turns = {200.f, 600.f};
    void updateSize(float y);
};

