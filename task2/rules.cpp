#include "rules.h"

Rules::Rules() {
	std::ifstream file("resources/cfg.txt");

	file >> maxAngleOppositeLane;

	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	file >> maxAngleUturn;

	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	file >> UturnAngleStart;
}

bool Rules::isUturnStarted(Car car, Road road) {
	float directionDegrees = car.direction * (180 / 3.14159f);

	if (car.x < road.center) {
		if (directionDegrees < 90 - UturnAngleStart) {
			return true;
		}
	} else {
		if (directionDegrees < 270 - UturnAngleStart) {
			return true;
		}
	}

	return false;
}

bool Rules::isUturnCorrect(Car car, Road road) {
	float centerDistance = abs(car.x - road.center);
	float angleShift = abs(50 - centerDistance) / 50 * 90;
	float directionDegrees = car.direction * (180 / 3.14159f);

	if (uTurnStartLeft) {
		if (car.x < road.center) { 
			if (
				(directionDegrees < 90 - angleShift + maxAngleUturn) 
				&& 
				((directionDegrees > 90 - angleShift - maxAngleUturn) || 
				(directionDegrees > 450 - angleShift - maxAngleUturn))) {
				return false;
			}
		} 
		else {
			if (((directionDegrees > 270 + angleShift - maxAngleUturn) &&
				((directionDegrees < 270 + angleShift + maxAngleUturn))) 
				|| 
				((directionDegrees > -90 + angleShift - maxAngleUturn) &&
				((directionDegrees < -90 + angleShift + maxAngleUturn)))) {
				return false;
			}
		}
	}
	else {
		if (car.x < road.center) {
			if ((directionDegrees < 90 + angleShift + maxAngleUturn) &&
				(directionDegrees > 90 + angleShift - maxAngleUturn)) {
				return false;
			}
		}
		else {
			if ((directionDegrees > 270 - angleShift - maxAngleUturn) &&
				(directionDegrees < 270 - angleShift + maxAngleUturn)) {
				return false;
			}
		}
	}

	return true;
}

bool Rules::isNearUturn(Car car, Road road) {
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

bool Rules::isCrossingLane(Car car, Road road) {
	if ((road.center - car.radius < car.x) && (road.center + car.radius > car.x)) {
		return true;
	}

	return false;
}

bool Rules::isMovingInOppositeDirection(Car car, Road road) {
	float directionDegrees = car.direction * (180 / 3.14159f);

	if (car.x < road.center) {
		if ((directionDegrees < 270 + maxAngleOppositeLane) && (directionDegrees > 270 - maxAngleOppositeLane)) {
			return true;
		}
	} 
	else {
		if ((directionDegrees > 90 - maxAngleOppositeLane) && (directionDegrees < 90 + maxAngleOppositeLane)) {
			return true;
		}
	}

	return false;
}

std::string Rules::checkAllRules(Car car, Road road) {
	if (isNearUturn(car, road)) {

		if (!makingUturn && isUturnStarted(car,road)) {
			uTurnStartLeft = car.x < road.center;
			makingUturn = true;
			incorrectUturn = false;
		}

		if (isUturnCorrect(car, road)) {
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

	if (isCrossingLane(car, road)) {
		return "Crossing solid line";
	}

	if (isMovingInOppositeDirection(car, road)) {
		return "Moving in the opposite direction";
	}

	return "0";
}