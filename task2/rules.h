#pragma once
#include "car.h"
#include "road.h"
#include <fstream>

class Rules {

private:
	float maxAngleOppositeLane;
	float maxAngleUturn;
	float UturnAngleStart;
	bool makingUturn = false;
	bool incorrectUturn = false;
	bool uTurnStartLeft = false;
	bool isUturnStarted(Car car, Road road);
	bool isUturnCorrect(Car car, Road road);
	bool isCrossingLane(Car car, Road road);
	bool isMovingInOppositeDirection(Car car, Road road);
	bool isNearUturn(Car car, Road road);

public:
	Rules();
	std::string checkAllRules(Car car, Road road);
};

