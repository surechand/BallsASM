#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable {
	sf::CircleShape ball;
	float posX, posY;
	float speedX, speedY;
	float radius;
	int id;
	bool canMove;

public:
	Ball() = default;

	Ball(float posX, float posY, float radius, float speedX, float speedY);

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	sf::CircleShape& getBall();

	float getPosX() const;

	void setPosX(float posX);

	float getPosY() const;

	void setPosY(float posY);

	float getSpeedX() const;

	void setSpeedX(float speedX);

	float getSpeedY() const;

	void setSpeedY(float speedY);

	float getAccX() const;

	float getAccY() const;

	float getRadius() const;

	int getId() const;

	void setId(int id);

	bool getCanMove() const;

	void setCanMove(bool canMove);
};
