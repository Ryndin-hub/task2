#include "car.h"
#include <cmath>

void Car::move() {
	x += speed * cos(direction);
	y += speed * sin(direction);
}

void Car::turnLeft() {
	direction -= turnSpeed;
	if (direction <= 0) direction += 6.28318;
}

void Car::turnRight() {
	direction += turnSpeed;
	if (direction >= 6.28318) direction -= 6.28318;
}