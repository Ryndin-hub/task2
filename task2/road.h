#pragma once
#include "vector"

class Road {

private:
    float minY = -400;
    float maxY = 800;
    float center = 200;
    std::vector<float> turns = { 200.f, 600.f };

public:
    float getCenter();
    int getNumberOfTurns();
    float getTurnByNumber(int i);
    void updateSize(float y);
};

