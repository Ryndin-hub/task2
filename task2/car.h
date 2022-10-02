#pragma once
#include "road.h"
#include <fstream>

class Car {

private:
    float speed;
    float turnSpeed;

public:
    Car();
    float radius = 20;
    float x = 100;
    float y = 100;
    float direction = 1.5708f;
    void moveForward(Road *road);
    void turnLeft();
    void turnRight();
};
