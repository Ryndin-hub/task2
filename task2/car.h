#pragma once
class Car {
private:
    float speed = 3;
    float turnSpeed = 0.05f;
public:
    float radius = 20;
    float x = 100;
    float y = 100;
    float direction = 1.5708f;
    void move();
    void turnLeft();
    void turnRight();
};
