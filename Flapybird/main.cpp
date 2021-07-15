#include <SFML/Graphics.hpp>
#include <string>
#include "flappyBirdGame.h"
using namespace std;
using namespace sf;







int main()
{
	srand(time(0));


	//gameScore.setColor(sf::Color::Black);

	sf::RenderWindow window(sf::VideoMode(flappyBirdGame::getWidth(), flappyBirdGame::getWidth()), "Flappy bird");
	flappyBirdGame game(window);
	window.setFramerateLimit(120);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.start();
	}

	return 0;
}

