#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include <Windows.h>




class tower {
	sf::Texture pic;
	sf::Sprite up;
	sf::Sprite down;
	sf::Vector2f coord;
	int distance = 400;
	bool started = false;
public:
	sf::Sprite& getUpSprite() { return up; }
	sf::Sprite& getDownSprite() { return down; }
	int getDistance()const { return distance; }
	tower() {

		pic.loadFromFile("bird\\Tower.png");
		down.setTexture(pic);
		coord.x = 1000;
		coord.y = rand() % 600 + 400;

		up.setTexture(pic);
		up.rotate(180);
	}
	void rebuild() {
		coord.x = 1000;
		coord.y = rand() % 600 + 400;
		started = false;
	}
	void show(sf::RenderWindow& window) {
		down.setPosition(coord);
		window.draw(down);
		up.setPosition(coord.x + 172, coord.y - distance);
		window.draw(up);
	}
	void start() {
		started = true;
	}
	sf::Vector2f getCoordinates()const { return coord; }
	void animate(sf::RenderWindow& window) {
		if (started) {
			coord.x -= 2;
			if (coord.x + 172 < 0) {
				coord.x = 1000;
				coord.y = rand() % 600 + 200;
				started = false;
			}
		}

		show(window);
	}
};