#pragma once
#include "bird.h"
#include "tower.h"



enum gameStates {
	begin,
	game,
	end
};

class flappyBirdGame {
	gameStates state;
	bird b;
	tower tow[4];
	static int width;
	static int height;
	int score = 0;
	int bestScore = 0;
	bool isTower = true;
	int curTower = -1;
	sf::Font f;
	Text gameScore;
	Texture backgroundImg;
	Sprite backGroundSprite;
	sf::RenderWindow& window;
	bool flag = true;
	bool isSpace = false;
public:
	flappyBirdGame(sf::RenderWindow& window) :window(window),
		b(sf::Vector2f(width, height)) {
		state = gameStates::begin;
		f.loadFromFile("bird\\gta.ttf");
		gameScore.setFont(f);
		gameScore.setCharacterSize(50);
		gameScore.setPosition(30, -10);
		gameScore.setScale(2, 2);
		backgroundImg.loadFromFile("bird\\fon.png");

		backGroundSprite.setTexture(backgroundImg);
		backGroundSprite.setScale(2, 2);
		//первая башня может начать двигаться
		tow[0].start();
	}
	static int getWidth() { return width; }
	static int getHeight() { return height; }

	void animateTowers() {


		for (size_t i = 0; i < 4; i++)
		{
			if (tow[i].getCoordinates().x + 172 < 1000 - 300) tow[((i == 3) ? 0 : i + 1)].start();
			tow[i].animate(window);
		}
	}
	void checkScore() {
		for (size_t i = 0; i < 4; i++)
		{
			if (b.getPosition().x + 245 * 0.3 >= tow[i].getCoordinates().x
				&& b.getPosition().x <= tow[i].getCoordinates().x + 172) {
				curTower = i;
				isTower = true;

			}
			else {
				if (curTower == i) {
					if (isTower)
						score++;
					curTower++;
					isTower = false;
					break;
				}
			}
		}

	}
	bool isGameOver() {
		//252*0.3 177*0.3
		for (size_t i = 0; i < 4; i++)
		{

			if (b.getPosition().x + 245 * 0.3 >= tow[i].getCoordinates().x
				&& b.getPosition().x <= tow[i].getCoordinates().x + 172) {

				if (b.getPosition().y + 150 * 0.3 >= tow[i].getCoordinates().y)
					return true;
				if (b.getPosition().y + 5 <= tow[i].getCoordinates().y - tow[i].getDistance())
					return true;
			}

		}


		if (b.getPosition().y >= height - 177 * 0.3)
			return true;
		return false;
	}
	void checkGameStatus() {
		if (state == gameStates::game) {
			if (isGameOver())
				state = gameStates::end;
		}
		if (state == gameStates::begin) {
			if (GetAsyncKeyState(VK_SPACE) && !isSpace) {
				state = gameStates::game;
				isSpace = true;
			}
		}
	}
	void start()
	{
		checkGameStatus();
		switch (state)
		{
		case gameStates::begin:
			if (!GetAsyncKeyState(VK_SPACE))
				isSpace = false;
			window.clear();
			window.draw(backGroundSprite);
			gameScore.setString(to_string(score));
			b.animate(100, window);
			window.draw(gameScore);
			window.display();

			break;
		case gameStates::game:

			flag = true;
			window.clear();
			window.draw(backGroundSprite);
			gameScore.setString(to_string(score));
			b.animate(100, window);
			animateTowers();
			b.fall();
			checkScore();
			window.draw(gameScore);
			//showGameOver();
			window.display();
			break;
		case gameStates::end:
			if (bestScore < score)
				bestScore = score;
			showGameOver();

			if (GetAsyncKeyState(VK_SPACE) && isSpace == false) {
				beforeStartGame();
				state = gameStates::begin;
				isSpace = true;
			}
			if (!GetAsyncKeyState(VK_SPACE))
				isSpace = false;
			break;
		}

	}
	void beforeStartGame() {
		for (size_t i = 0; i < 4; i++)
		{
			tow[i].rebuild();
		}
		tow[0].start();
		score = 0;
		curTower = -1;
		b.setCenterPosition(width, height);

	}
	void showGameOver() {
		Text gameOver;
		gameOver.setFont(f);
		gameOver.setCharacterSize(50);
		gameOver.setOrigin(100, 100);
		gameOver.setPosition(width / 2, height / 2);
		gameOver.setScale(2, 2);
		gameOver.setFillColor(Color::Red);
		//gameOver.setStyle(Text::Style::StrikeThrough);
		string str = "NOMPA4EHO\n";
		str += "best " + to_string(bestScore);
		str += "\nyour " + to_string(score);
		gameOver.setString(str);
		window.draw(gameOver);
		if (flag) {
			window.display();
			flag = false;
		}

	}
};

int flappyBirdGame::width = 1000;
int flappyBirdGame::height = 1000;