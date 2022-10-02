#include "car.h"

Car::Car() {
	std::ifstream file("resources/cfg.txt");

	for (int i = 0; i < 3; i++) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	file >> speed;

	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	file >> turnSpeed;
}

void Car::moveForward(Road *road) {
	x += speed * cos(direction);
	y += speed * sin(direction);

	road->updateSize(y);
}

void Car::turnLeft() {
	direction -= turnSpeed;
	if (direction <= 0) direction += 3.14159f * 2;
}

void Car::turnRight() {
	direction += turnSpeed;
	if (direction >= 3.14159f * 2) direction -= 3.14159f * 2;
}