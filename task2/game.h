#pragma once
#include <SFML/Graphics.hpp>
#include "car.h"
#include "road.h"
#include "rules.h"

class Game {

private:
    const int gameWidth = 400;
    const int gameHeight = 800;
    sf::RenderWindow window;
    sf::Text message;
    std::vector<std::string> currentMessages = {};
    std::vector<int> currentMessagesAge = {};
    Car car;
    Road road;
    Rules rules;
    bool moving_up = false;
    bool moving_right = false;
    bool moving_left = false;
    void editMessage(std::string newMessage);

public:
    void run();
};
