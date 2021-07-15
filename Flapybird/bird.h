#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include <Windows.h>
#pragma comment(lib, "User32.lib")
using namespace std;
using namespace sf;


class bird {
	string dir = "bird\\bird";
	int curNum = 0;
	int timeFromLastChange = 0;
	Sprite s;
	Texture t;
	Vector2f position{ 450,450 };
	double boost = 0.0005;
	double speed = 0;
	int timeFromStart = clock();
	bool isSpace = 0;
public:
	bird(Vector2f ScreenSize) {
		this->position.x = ScreenSize.x / 2 - 252 * 0.3 / 2;
		this->position.y = ScreenSize.y / 2 - 177 * 0.3 / 2;
	}
	Sprite& getSprite() { return s; }
	Vector2f& getPosition() { return position; }
	void setCenterPosition(float x, float y) {
		this->position.x = x / 2 - 252 * 0.3 / 2;
		this->position.y = y / 2 - 177 * 0.3 / 2;
		speed = 0;
	}

	void animate(int periodInMs, RenderWindow& window) {
		int curTime = clock();
		string d = dir + to_string(curNum) + ".png";

		t.loadFromFile(d);
		s.setTexture(t);
		s.setPosition(position);
		s.setScale(0.3, 0.3);
		window.draw(s);
		if (curTime - timeFromLastChange >= periodInMs)
		{
			timeFromLastChange = clock();
			curNum++;
			if (curNum == 3)
				curNum = 0;
		}
	}
	void fall() {
		this->up();
		int curTime = clock();
		speed += (curTime - timeFromStart) * boost;
		position.y += speed;
	}
	void up() {
		if (GetAsyncKeyState(VK_SPACE) && isSpace == 0) {
			speed = 0;
			speed = -4;
			timeFromStart = clock();
			isSpace = 1;
		}
		if (!GetAsyncKeyState(VK_SPACE)) isSpace = 0;
	}
};