#include "car.h"
#include <cmath>

void Car::move(Road *road) {
	x += speed * cos(direction);
	y += speed * sin(direction);
	road->updateSize(y);
}

void Car::turnLeft() {
	direction -= turnSpeed;
	if (direction <= 0) direction += 6.28318f;
}

void Car::turnRight() {
	direction += turnSpeed;
	if (direction >= 6.28318) direction -= 6.28318f;
}