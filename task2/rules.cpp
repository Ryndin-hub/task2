#include "rules.h"

Rules::Rules() {
	std::ifstream file("resources/cfg.txt");
	file >> maxAngleOppositeLane;
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	file >> maxAngleUturn;
}

bool Rules::checkUturnStart(Car car, Road road) {
	if (car.x < road.center) {
		if (car.direction * (180 / 3.14159) < 90 - 15) {
			return true;
		}
	} else {
		if (car.direction * (180 / 3.14159) < 270 - 15) {
			return true;
		}
	}
	return false;
}

bool Rules::correctUturnCheck(Car car, Road road) {
	float centerDistance = abs(car.x - road.center);
	float angleShift = abs(50 - centerDistance) / 50 * 90;
	if (uTurnStartLeft) {
		if (car.x < road.center) {
			if ((car.direction * (180 / 3.14159) < 90 - angleShift + maxAngleUturn) && (((car.direction * (180 / 3.14159) > 90 - angleShift - maxAngleUturn)) || ((car.direction * (180 / 3.14159) > 450 - angleShift - maxAngleUturn)))) {
				return false;
			}
		}
		else {
			if (((car.direction * (180 / 3.14159) > 270 + angleShift - maxAngleUturn) && ((car.direction * (180 / 3.14159) < 270 + angleShift + maxAngleUturn))) || ((car.direction * (180 / 3.14159) > -90 + angleShift - maxAngleUturn) && ((car.direction * (180 / 3.14159) < -90 + angleShift + maxAngleUturn)))) {
				return false;
			}
		}
	}
	else {
		if (car.x < road.center) {
			if ((car.direction * (180 / 3.14159) < 90 + angleShift + maxAngleUturn) && (car.direction * (180 / 3.14159) > 90 + angleShift - maxAngleUturn)) {
				return false;
			}
		}
		else {
			if ((car.direction * (180 / 3.14159) > 270 - angleShift - maxAngleUturn) && (car.direction * (180 / 3.14159) < 270 - angleShift + maxAngleUturn)) {
				return false;
			}
		}
	}
	return true;
}

bool Rules::nearTurnCheck(Car car, Road road) {
	for (int i = 0; i < road.turns.size(); i++) {
		float x1 = car.x;
		float y1 = car.y;
		float x2 = road.center;
		float y2 = road.turns[i];
		if (pow(x2 - x1, 2) + pow(y2 - y1, 2) < 1000) {
			return true;
		}
	}
	return false;
}

bool Rules::crossLaneCheck(Car car, Road road) {
	if ((road.center - car.radius < car.x) && (road.center + car.radius > car.x)) {
		return true;
	}
	return false;
}

bool Rules::oppositeLaneCheck(Car car, Road road) {
	if (car.x < road.center) {
		if ((car.direction * (180 / 3.14159) < 270 + maxAngleOppositeLane) && (car.direction * (180 / 3.14159) > 270 - maxAngleOppositeLane)) {
			return true;
		}
	}
	if (car.x >= road.center) {
		if ((car.direction * (180 / 3.14159) > 90 - maxAngleOppositeLane) && (car.direction * (180 / 3.14159) < 90 + maxAngleOppositeLane)) {
			return true;
		}
	}
	return false;
}

std::string Rules::checkAllRules(Car car, Road road) {
	if (nearTurnCheck(car, road)) {
		if (!makingUturn && checkUturnStart(car,road)) {
			uTurnStartLeft = car.x < road.center;
			makingUturn = true;
			incorrectUturn = false;
		}
		if (correctUturnCheck(car, road)) {
			incorrectUturn = true;
			return "Incorrect Uturn";
		}
		if (makingUturn) {
			return "Makes a Uturn";
		}
	}
	if (makingUturn) {
		makingUturn = false;
		if (!incorrectUturn) {
			return "Correct Uturn";
		}
	}
	if (crossLaneCheck(car, road) == true) {
		return "Crossing solid line";
	}
	if (oppositeLaneCheck(car, road) == true) {
		return "Moving in the opposite direction";
	}
	return "0";
}