#include "road.h"

float Road::getCenter() {
	return center;
}

int Road::getNumberOfTurns() {
	return turns.size();
}

float Road::getTurnByNumber(int i) {
	return turns[i];
}

void Road::updateSize(float y) {
	y -= 500;
	if (y < minY) {
		float randomNewY = minY - std::rand() % 500;

		turns.push_back(randomNewY);
		minY = randomNewY - 200;
	}

	y += 1000;
	if (y > maxY) {
		float randomNewY = maxY + std::rand() % 500;

		turns.push_back(randomNewY);
		maxY = randomNewY + 200;
	}
}