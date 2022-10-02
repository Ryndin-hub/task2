#include "car.h"
#include <cmath>

Car::Car() {
	std::ifstream file("resources/cfg.txt");
	for (int i = 0; i < 2; i++) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	file >> speed;
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	file >> turnSpeed;
}

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