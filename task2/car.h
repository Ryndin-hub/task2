#pragma once
#include "road.h"
#include <fstream>

class Car {

private:
    float radius = 20;
    float x = 100;
    float y = 100;
    float direction = 1.5708f;
    float speed;
    float turnSpeed;

public:
    Car();
    float getX();
    float getY();
    float getDirection();
    float getRadius();
    void moveForward(Road *road);
    void turnLeft();
    void turnRight();
};
