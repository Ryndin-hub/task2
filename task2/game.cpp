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

	sf::CircleShape carCircle;
	carCircle.setRadius(car.getRadius());
	carCircle.setOutlineThickness(1);
	carCircle.setOutlineColor(sf::Color::White);
	carCircle.setFillColor(sf::Color::Black);

	sf::RectangleShape carDirectionLine(sf::Vector2f(20, 1));
	carDirectionLine.setFillColor(sf::Color::White);
	carDirectionLine.rotate(0);

	sf::RectangleShape roadLeftLine(sf::Vector2f(800, 1));
	roadLeftLine.setFillColor(sf::Color::White);
	roadLeftLine.setPosition(50, 0);
	roadLeftLine.rotate(90);

	sf::RectangleShape roadCenterLine(sf::Vector2f(800, 1));
	roadCenterLine.setFillColor(sf::Color::White);
	roadCenterLine.setPosition(200, 0);
	roadCenterLine.rotate(90);

	sf::RectangleShape roadRightLine(sf::Vector2f(800, 1));
	roadRightLine.setFillColor(sf::Color::White);
	roadRightLine.setPosition(350, 0);
	roadRightLine.rotate(90);

	sf::Font font;
	font.loadFromFile("resources/sansation.ttf");
	message.setFont(font);
	message.setCharacterSize(15);
	message.setStyle(sf::Text::Bold);
	message.setPosition(0, 0);
	message.setFillColor(sf::Color::Red);

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
			car.moveForward(&road);
		}

		if (moving_left) {
			car.turnLeft();
		}

		if (moving_right) {
			car.turnRight();
		}

		window.clear(sf::Color::Black);

		carCircle.setPosition(car.getX() - car.getRadius(), gameHeight / 2 - car.getRadius());
		carDirectionLine.setPosition(car.getX(), gameHeight / 2.0);
		carDirectionLine.setRotation(car.getDirection() * (180 / 3.14159f));

		window.draw(roadLeftLine);
		window.draw(roadCenterLine);
		window.draw(roadRightLine);

		for (int i = 0; i < road.getNumberOfTurns(); i++) {
			sf::RectangleShape turn(sf::Vector2f(100, 3));
			turn.setFillColor(sf::Color::Black);
			turn.setPosition(road.getCenter(), road.getTurnByNumber(i) - 50 - car.getY() + gameHeight / 2);
			turn.rotate(90);
			window.draw(turn);
		}

		window.draw(carCircle);
		window.draw(carDirectionLine);

		editMessage(rules.checkAllRules(car, road));

		window.draw(message);

		window.display();
	}
}