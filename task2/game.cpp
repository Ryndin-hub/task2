#include "game.h"

void Game::editMessage(std::string newMessage) {
	if (newMessage != "0") {
		bool isNew = true;
		for (int i = 0; i < currentMessages.size(); i++) {
			if (newMessage == currentMessages[i]) {
				currentMessagesAge[i] = 70;
				isNew = false;
			}
		}
		if (isNew) {
			currentMessagesAge.push_back(70);
			currentMessages.push_back(newMessage);
		}
	}
	for (int i = 0; i < currentMessages.size(); i++) {
		currentMessagesAge[i] -= 1;
		if (currentMessagesAge[i] <= 0) {
			currentMessagesAge.erase(currentMessagesAge.begin() + i);
			currentMessages.erase(currentMessages.begin() + i);
			i--;
		}
	}
	std::string completeText = "";
	for (int i = 0; i < currentMessages.size(); i++) {
		completeText += currentMessages[i];
		completeText += "\n";
	}
	message.setString(completeText);
}

void Game::run() {
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Road", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::CircleShape carBall;
	carBall.setRadius(20);
	carBall.setOutlineThickness(1);
	carBall.setOutlineColor(sf::Color::White);
	carBall.setFillColor(sf::Color::Black);

	sf::RectangleShape carLine(sf::Vector2f(20, 1));
	carLine.setFillColor(sf::Color::White);
	carLine.rotate(0);

	sf::RectangleShape roadLeft(sf::Vector2f(800, 1));
	roadLeft.setFillColor(sf::Color::White);
	roadLeft.setPosition(50, 0);
	roadLeft.rotate(90);

	sf::RectangleShape roadCenter(sf::Vector2f(800, 1));
	roadCenter.setFillColor(sf::Color::White);
	roadCenter.setPosition(200, 0);
	roadCenter.rotate(90);

	sf::RectangleShape roadRight(sf::Vector2f(800, 1));
	roadRight.setFillColor(sf::Color::White);
	roadRight.setPosition(350, 0);
	roadRight.rotate(90);

	sf::Font font;
	font.loadFromFile("resources/sansation.ttf");
	message.setFont(font);
	message.setCharacterSize(15);
	message.setPosition(0, 0);
	message.setFillColor(sf::Color::Red);
	message.setString("rules.checkAllRules(car, road)");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Right)
					moving_right = true;
				else if (event.key.code == sf::Keyboard::Left)
					moving_left = true;
				else if (event.key.code == sf::Keyboard::Up)
					moving_up = true;
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Right)
					moving_right = false;
				else if (event.key.code == sf::Keyboard::Left)
					moving_left = false;
				else if (event.key.code == sf::Keyboard::Up)
					moving_up = false;
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		if (moving_up) {
			car.move(&road);
		}
		if (moving_left) {
			car.turnLeft();
		}
		if (moving_right) {
			car.turnRight();
		}

		window.clear(sf::Color::Black);

		carBall.setPosition(car.x - car.radius, gameHeight / 2 - car.radius);
		carLine.setPosition(car.x, gameHeight / 2);
		carLine.setRotation(car.direction * (180 / 3.14159f));

		window.draw(roadLeft);
		window.draw(roadCenter);
		window.draw(roadRight);

		for (int i = 0; i < road.turns.size(); i++) {
			sf::RectangleShape turn(sf::Vector2f(100, 3));
			turn.setFillColor(sf::Color::Black);
			turn.setPosition(road.center,road.turns[i] - 50 - car.y + gameHeight / 2);
			turn.rotate(90);
			window.draw(turn);
		}

		window.draw(carBall);
		window.draw(carLine);

		editMessage(rules.checkAllRules(car, road));

		window.draw(message);

		window.display();
	}
}