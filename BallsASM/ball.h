#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable {
	sf::CircleShape ball;
	float posX, posY;
	float speedX, speedY;
	float accX, accY;
	float radius;
	int id;
	bool canMove;
public:
	Ball() = default;

	Ball(float posX, float posY, float radius);

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	sf::CircleShape& getBall();

	float getPosX() const;

	void setPosX(float posX);

	float getPosY() const;

	void setPosY(float posY);

	float getSpeedX() const;

	float getSpeedY() const;

	float getAccX() const;

	float getAccY() const;

	float getRadius() const;

	int getId() const;

	void setId(int id);

	bool getCanMove() const;

	void setCanMove(bool canMove);
};
