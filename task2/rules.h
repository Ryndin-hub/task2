#pragma once
#include "car.h"
#include "road.h"
#include <fstream>

class Rules {
private:
	float maxAngleOppositeLane;
	float maxAngleUturn;
	bool makingUturn = false;
	bool incorrectUturn = false;
	bool correctUturnCheck(Car car, Road road);
	bool crossLaneCheck(Car car, Road road);
	bool oppositeLaneCheck(Car car, Road road);
	bool nearTurnCheck(Car car, Road road);
public:
	Rules();
	std::string checkAllRules(Car car, Road road);
};

